#include "hash_tables.h"

/**
 * shash_table_create - Creates a hash table
 * @size: size of array
 * Return: Pointer to table or NULL
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *newhash;

	if (size < 1)
		return (NULL);
	newhash = malloc(sizeof(shash_table_t));
	if (newhash == NULL)
		return (NULL);

	newhash->size = size;
	newhash->shead = NULL;
	newhash->stail = NULL;
	newhash->array = calloc(size, sizeof(shash_node_t *));
	if ((newhash->array) == NULL)
	{
		free(newhash);
		return (NULL);
	}
	return (newhash);
}

/**
 * shash_table_set - adds element to a hash table
 * @ht: hash table to add or update key/value to
 * @key: The Key
 * @value: value to be added or updated
 * Return: 1 on success, 0 on fail
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *newnode, *tmp, *tmp2;
	unsigned long key_idx;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);
	key_idx = hash_djb2((const unsigned char *)key) % ht->size;
	tmp = ht->array[key_idx];
	for (; tmp; tmp = tmp->next)
	{
		if (!strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return (1);
		}
	}
	newnode = malloc(sizeof(shash_node_t));
	if (!newnode)
		return (0);
	newnode->key = strdup(key), newnode->value = strdup(value);
	newnode->next = ht->array[key_idx], ht->array[key_idx] = newnode;
	if (!ht->shead)
	{
		ht->shead = newnode, ht->stail = newnode;
		newnode->sprev = NULL, newnode->snext = NULL;
		return (1);
	}
	if (strcmp(ht->shead->key, key) > 0)
	{
		newnode->snext = ht->shead, newnode->sprev = NULL;
		ht->shead->sprev = newnode, ht->shead = newnode;
		return (1);
	}
	tmp2 = ht->shead;
	for (; tmp2->snext; tmp2 = tmp2->snext)
	{
		if (strcmp(tmp2->key, key) > 0)
		{
			newnode->sprev = tmp2->sprev, newnode->snext = tmp2;
			tmp2->sprev->snext = newnode, tmp2->sprev = newnode;
			return (1);
		}
	}
	newnode->sprev = ht->stail, newnode->snext = NULL;
	ht->stail->snext = newnode, ht->stail = newnode;
	return (1);
}
/**
 * shash_table_get - Retrieves value associated with a key
 * @ht: hash table to check
 * @key: key to find
 * Return: value or NULL on fail
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int key_idx;
	shash_node_t *tmp;

	if (ht == NULL || key == NULL)
		return (NULL);

	key_idx = hash_djb2((const unsigned char *)key) % ht->size;
	tmp = ht->array[key_idx];
	if (!tmp)
		return (NULL);
	for (; tmp; tmp = tmp->next)
	{
		if (!strcmp(tmp->key, key))
			return (tmp->value);
	}
	return (NULL);
}

/**
 * shash_table_print - prints the sorted hash table
 * @ht: hash table to check
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *tmp;

	if (!ht)
		return;
	tmp = ht->shead;
	putchar('{');
	for (; tmp; tmp = tmp->snext)
	{
		printf("'%s': '%s'%s", tmp->key, tmp->value, tmp->snext ? ", " : "");
	}
	putchar('}');
	putchar('\n');
}

/**
 * shash_table_print_rev - prints the sorted hash table recursively
 * @ht: hash table to check
 */
void shash_table_print_rev(const shash_table_t *ht)
{
shash_node_t *tmp;

	if (!ht)
		return;
	tmp = ht->stail;
	putchar('{');
	for (; tmp; tmp = tmp->sprev)
	{
		printf("'%s': '%s'%s", tmp->key, tmp->value, tmp->sprev ? ", " : "");
	}
	putchar('}');
	putchar('\n');
}

/**
 * shash_table_delete - does what it says
 * @ht: table to delete
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *tmp, *node;

	if (!ht)
		return;
	node = ht->shead;
	while (node)
	{
		tmp = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = tmp;
	}
	free(ht->array);
	free(ht);
}
