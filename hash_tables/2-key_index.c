#include "hash_tables.h"

/**
 * key_index - finds the index of a key
 * @key: key provided
 * @size: size of hash table
 * Return: index of key in hash table
 */

unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
