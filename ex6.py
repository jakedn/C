#!usr/bin/sh

import re
import sys
from os import listdir,getcwd
from os.path import isfile,join,isdir,exists
from enum import Enum


variablecounter = 1024
places = {}
variables = {}

def getfiles(directory):

    cwd = getcwd()
    if not exists(directory):
        if exists(join(cwd, directory)):
            directory = join(cwd, directory)
        else:
            return []
    if isdir(directory):
        return [join(directory, f) for f in listdir(directory)
                if (isfile(join(directory, f)) and '.asm' == f[-4:])]
    if isfile(directory):
        return [directory]

    # if we get here we are not on a file or a directory
    return []


class TokenType(Enum):
    SPACE = r'[\t\s]*'
    AT = r'(?P<AT>@)'
    EQ = r'(?P<EQ>=)'
    VAR = r'(?P<VAR>[a-z_A-Z]\w*)'
    ADDRESS = r'\([\s\t]*(?P<ADDRESS>\w+)[\s\t]*\)'
    BINOP = r'(?P<BINOP>[+-\|&\*])'
    MONOP = r'(?P<MONOP>!|>{2}|<{2})'
    NUM = r'(?P<NUM>[0-9]{1,15})'
    JUMP = r';(?P<JUMP>[JNEQLTG]{3})'
    NL = r'(?P<NL>\n)'
    COMMENT = r'//.*'


class Token:
    def __init__(self, typeOfToken, value):
        self.type = typeOfToken
        self.value = value

    def __str__(self):
        return '('+self.type+' '+self.value+')'

    def isa(self,tokentype):
        return self.type == tokentype.name


# creates a compiled pattern for regex use based on all tokentypes
def makeMatcher():
    pattern = r''
    for ttype in TokenType.__members__:
        pattern += r'|' + ttype.value

    # we have "|" in the beginning of pattern that needs to be taken out
    return re.compile(pattern[1:])


# breaks file at a given directory into tokens
def tokenizer(directory):
    tokens = []
    f = open(directory, "r")
    file_content = f.read()
    matcher = makeMatcher()
    nextmatch = matcher.match(file_content)
    while nextmatch:
        for name in matcher.groupindex:
            if nextmatch.group(name) != None:
                tokens.append(Token(name, nextmatch.group()))
                break

        # the next line takes out the part of the string that was matched
        file_content = file_content[nextmatch.group().__len__():]
        nextmatch = matcher.match(file_content)
    f.close()
    return tokens


# finds all the places saved by name and removes them from tokens
def preassembler(tokens):
    global places, variables, variablecounter
    counter, commandcounter = 0, 0
    maxc = len(tokens)

    while counter < maxc:
        if tokens[counter].isa(TokenType.ADDRESS):
            places[tokens[counter].value] = commandcounter
            tokens.pop(counter)
            maxc -= 1
            pop = True
            # we take out any NL tokens after ADDRESS so they dont make
            # the commandcounter go up falsely
            while counter < maxc and pop:
                if tokens[counter].isa(TokenType.NL):
                    tokens.pop(counter)
                    maxc -= 1
                else:
                    pop = False
            continue

        # we know there is only 1 command if we pass a \n
        if tokens[counter].isa(TokenType.NL):
            commandcounter += 1
        counter += 1
    counter = 0
    while counter < maxc:
        if tokens[counter].isa(TokenType.AT):
            if tokens[counter+1].isa(TokenType.VAR) and \
                            tokens[counter+1].value not in places:
                variables[tokens[counter+1].value] = variablecounter
                variablecounter += 1
                counter += 1
        counter += 1
    return tokens

# gets next line of tokens (tokens until the next nl)
def getLine(tokens):
    line = []
    foundNL = 0
    while not foundNL and len(tokens):
        if tokens[0].isa(TokenType.NL):
            tokens.pop(0)
            foundNL = 1
        else:
            line.append(tokens.pop(0))
    return line, tokens


def jumpdigs(jump):
    if jump == 'JGT':
        return '001'
    if jump == 'JEQ':
        return '010'
    if jump == 'JGE':
        return '011'
    if jump == 'JLT':
        return '100'
    if jump == 'JNE':
        return '101'
    if jump == 'JLE':
        return '110'
    if jump == 'JMP':
        return '111'
    return '000'


def assembleLine(line):
    global variablecounter, places, variables
    maxc = len(line)
    c = 0
    if line[c].isa(TokenType.AT):
        c += 1

        if line[c].isa(TokenType.NUM):
            command = format(int(line[c].value),'016b')
            return command

        if line[c].value in places:
            command = format(int(places[line[c].value]),'016b')
            return command

        if line[c].value in variables:
            command = format(int(variables[line[c].value]),'016b')
        else:   # doesnt exist in the program
            command = '-1'

        return command


    noEQ = False
    commandjump = ''
    a, c1, c2, c3, c4, c5, c6, d1, d2, d3 = 10*['0']
    x,y = 2*['1']
    while c < maxc:
        if line[c].isa(TokenType.VAR):
            if noEQ:
                if 'A' in line[c].value:
                    d1 = '1'
                if 'D' in line[c].value:
                    d2 = '1'
                if 'M' in line[c].value:
                    d3 = '1'
            else:   # we passed an equal sign

                #TODO

        if line[c].isa(TokenType.BINOP):
            if line[c-1].isa(TokenType.EQ) and line[c].value == '-':
                if line[c+1].value == '1':
                    c1, c2, c3, c4, c5, c6 = ['1', '1', '1', '0', '1', '0']
                if line[c+1].value == 'A':
                    c1, c2, c3, c4, c5, c6 = ['1', '1', '0', '0', '1', '1']
                if line[c+1].value == 'M':
                    c1, c2, c3, c4, c5, c6 = ['1', '1', '0', '0', '1', '1']
                    a = '1'
                if line[c+1].value == 'D':
                    c1, c2, c3, c4, c5, c6 = ['0', '0', '1', '1', '1', '1']
                else:
                    return '-1'
                c += 2
                continue
            else:
                result = binopcmd(line[c], line[c-1], line[c+1]) #TODO make binaryop
                if result == '-1':
                    return result
                c1, c2, c3, c4, c5, c6 = result
        if line[c].isa(TokenType.EQ):
            if not noEQ:
                return '-1'
            noEQ = True

        if line[c].isa(TokenType.JUMP):
            commandjump = line[c].value

        c += 1

    return '1'+x+y+c1+c2+c3+c4+c5+c6+d1+d2+d3+jumpdigs(commandjump)


# takes out redundant \n in from the beginning of the list
def takeNLout(tokens):
    # we take out any leading \n without counting commands
    takeout = True
    counter = 0
    maxc = len(tokens)
    while counter < maxc and takeout:
        if tokens[counter].isa(TokenType.NL):
            tokens.pop(counter)
            maxc -= 1
        else:
            takeout = False
    return tokens


def main():
    global variablecounter, places, variables
    args = sys.argv
    for f in getfiles(args[0]):
        variablecounter, places, variables = 1024, {}, {}
        commands, lines = [], []
        tokens = tokenizer(f)
        tokens = takeNLout(tokens)
        tokens = preassembler(tokens)
        tokens = takeNLout(tokens)
        while tokens != []:
            line, tokens = getLine(tokens)
            lines.append(line)
            tokens = takeNLout(tokens)
        hackfile = open(f[:-4]+'.hack','w')
        hackfile.writelines([assembleLine(line) for line in lines])
        hackfile.close()

    return 0