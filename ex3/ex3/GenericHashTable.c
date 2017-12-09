#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "TableErrorHandle.h"
#include "GenericHashTable.h"

#define TRUE 1
#define FALSE 0
#define RESIZE_INCREMENT 2

typedef struct Table{
    size_t originSize;
    size_t size;
    void **tableKeys;
    DataP *tableData;
    CloneKeyFcn cloneKey;
    FreeKeyFcn freeKey;
    HashFcn hash;
    PrintKeyFcn printKey;
    PrintDataFcn printData;
    ComparisonFcn compare;

}Table;

/**
 * @brief Allocate memory for a hash table with which uses the given functions.
 * tableSize is the number of cells in the hash table.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */

TableP createTable(size_t tableSize, CloneKeyFcn cloneKey, FreeKeyFcn freeKey
        ,HashFcn hfun,PrintKeyFcn printKeyFun, PrintDataFcn printDataFun
        , ComparisonFcn fcomp)
{
    if(cloneKey == NULL || freeKey == NULL || hfun == NULL || printKeyFun == NULL ||
            printDataFun == NULL || fcomp == NULL)
    {
        return NULL;
    }
    TableP newTable = (TableP) malloc(sizeof(Table));
    if(newTable == NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    newTable->originSize = tableSize;
    newTable->size = tableSize;
    newTable->cloneKey = cloneKey;
    newTable->freeKey = freeKey;
    newTable->hash = hfun;
    newTable->printKey = printKeyFun;
    newTable->printData = printDataFun;
    newTable->compare = fcomp;
    newTable->tableKeys = malloc(tableSize * sizeof(void*));
    newTable->tableData = malloc(tableSize * sizeof(DataP));
    if(newTable->tableKeys == NULL || newTable->tableData == NULL)
    {
        reportError(MEM_OUT);
        return NULL;
    }
    return newTable;
}

//todo
/**
 * @brief
 * @param table
 * @param key
 * @param object
 * @return
 */
static int updateSize(const TableP table, const void* key, DataP object)
{
    assert(table != NULL && key != NULL && object != NULL);
    DataP *newData = malloc(table->size * RESIZE_INCREMENT * sizeof(DataP));
    void ** newKeys = malloc(table->size * RESIZE_INCREMENT * sizeof(void*));
    if(newData == NULL || newKeys == NULL)
    {
        reportError(MEM_OUT);
        return FALSE;
    }
    for(int i = 0; i < table->size; i++)
    {
        newData[RESIZE_INCREMENT * i] = table->tableData[i];
        newKeys[RESIZE_INCREMENT * i] = table->tableKeys[i];
    }
    table->size *= RESIZE_INCREMENT;
    free(table->tableKeys);
    free(table->tableData);
    table->tableData = newData;
    table->tableKeys = newKeys;
    int c = (table->hash)(key, table->size);
    size_t ratio = table->size / table->originSize;
    int index = c * (int) ratio + 1;                //the +1 is so its put in an open odd number spot
    table->tableKeys[index] = (table->cloneKey)(key);
    if(table->tableKeys[index] == NULL)
    {
        return FALSE;
    }
    table->tableData[index] = object;
    return TRUE;
}


/**
 * @brief Insert an object to the table with key.
 * If all the cells appropriate for this object are full, duplicate the table.
 * If run out of memory, report
 * MEM_OUT and do nothing (the table should stay at the same situation
 * as it was before the duplication).
 * If everything is OK, return true. Otherwise (an error occured) return false;
 */
int insert(const TableP table, const void* key, DataP object)
{
    if(table == NULL || key == NULL || object == NULL)
    {
        return FALSE;
    }
    int i, c = (table->hash)(key, table->size);
    size_t ratio = table->size / table->originSize;
    int index = c * (int) ratio, maxIndex = (c + 1) * (int) ratio;
    for(i = index; i < maxIndex; i++)
    {
        if((table->compare)(table->tableKeys[i], key) == 0)
        {
            table->tableData = object;
            return TRUE;
        }
    }
    for(i = index; i < maxIndex; i++)
    {
        if(table->tableKeys[i] == NULL)
        {
            table->tableKeys[i] = (table->cloneKey)(key);
            if(table->tableKeys[i] == NULL)
            {
                return FALSE;
            }
            table->tableData[i] = object;
            return TRUE;
        }
    }
    //if we got here it means there is no space for the new data in our table
    return updateSize(table, key, object);
}


/**
 * @brief remove an data from the table.
 * If everything is OK, return the pointer to the ejected data. Otherwise return NULL;
 */
DataP removeData(TableP table, const void* key)
{
    assert(table != NULL && key != NULL);
    for(int i = 0; i < table->size; i++)
    {
        if(!(table->compare)(table->tableKeys[i], key))
        {
            (table->freeKey)(table->tableKeys[i]);
            DataP temp = table->tableData[i];
            table->tableData[i] = NULL;
            return temp;
        }
    }
//todo get ansewr about weather or not to free data
}



/**
 * @brief Search the table and look for an object with the given key.
 * If such object is found fill its cell number into arrCell (where 0 is the
 * first cell).
 * If the key was not found, fill both pointers with value of -1.
 * return pointer to the data or null
 */
DataP findData(const TableP table, const void* key, int* arrCell)
{
    assert(table != NULL && key != NULL && arrCell != NULL);
    for(int i = 0; i < table->size; i++)
    {
        if(!(table->compare)(table->tableKeys[i], key))
        {
            *arrCell = i;
            return table->tableData[i];
        }
    }
    *arrCell = -1;
    return NULL;
}




/**
 * @brief return a pointer to the data that exist in the table in cell number arrCell (where 0 is the
 * first cell).
 * If such data not exist return NULL
 */
DataP getDataAt(const TableP table, int arrCell)
{
    assert(table != NULL);
    if(!(arrCell >= 0 && arrCell <= table->size))
    {
        return NULL;
    }
    return table->tableData[arrCell];
}

/**
 * @brief return the pointer to the key that exist in the table in cell number arrCell (where 0 is the
 * first cell).
 * If such key not exist return NULL
 */
ConstKeyP getKeyAt(const TableP table, int arrCell)
{
    assert(table != NULL);
    if(!(arrCell >= 0 && arrCell <= table->size))
    {
        return NULL;
    }
    return table->tableKeys[arrCell];
}

/**
 * @brief Print the table (use the format presented in PrintTableExample).
 */
void printTable(const TableP table)
{
    //TODO check if it meets requirments
    if(table == NULL)
    {
        return;
    }
    for(int i = 0; i < table->size; i++) {
        printf("[%d]", i);
        if(table->tableKeys[i] != NULL)
        {
            (table->printKey)(table->tableKeys[i]);
            printf(",");
            (table->printData)(table->tableData[i]);
        }
    printf("\t\n");
    }
}


/**
 * @brief Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
void freeTable(TableP table)
{
//TODO see if free is needed to check null or if it was freed before
    if(table == NULL)
    {
        return;
    }
    for(int i = 0; i < table->size; i++)
    {
        (*(table->freeKey))(table->tableKeys[i]);
        //todo fix next line
        //free(table->tableData[i]);
    }
    free(table->tableData);
    free(table->tableKeys);
    free(table);
}

