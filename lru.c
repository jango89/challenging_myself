/*****************
 * Least Recently Used
 * The oldest region (least recently used) is substituted if the given region is not found
 *
 * find(10) -> 10 -1 -1 -1 -1
 * find(11) -> 10 11 -1 -1 -1
 * find(12) -> 10 11 12 -1 -1
 * find(13) -> 10 11 12 13 -1
 * find(14) -> 10 11 12 13 14
 * 
 * find(10) -> 10 11 12 13 14
 * 
 * find(50) -> 10 50 12 13 14
*/

/*
This method helps to add the element as the first item into our array and 
pops out the least recently used item which is present as the last index of the array.
*/
void add_element_as_recently_used_and_remove_last_recently_used(int memory_region_id);

/*
This method helps to move the item to the first index in the array and shift the other elements,
which helps us to understand this is the most recently used item.
*/
void move_element_to_recently_used_position(int index_found);

typedef struct MemoryRegion
{
    int value;
} MemoryRegion;

/*The data structure helps to keep the recently used memoryIds.
Sorted or arranged always based on "most recently used" to "least recently used"
*/
MemoryRegion recent_used_memory_regions[5] = {{-1, -1, -1, -1, -1}};

MemoryRegion *find(int memory_region_id)
{
    int index_found = -1;
    for (int index = 0; index < 5; index++)
    {
        if (recent_used_memory_regions[index].value == memory_region_id)
        {
            index_found = index;
            break;
        }
    }

    if (index_found > -1)
    {
        move_element_to_recently_used_position(index_found);
    }
    else
    {
        add_element_as_recently_used_and_remove_last_recently_used(memory_region_id);
    }
    return &recent_used_memory_regions[0];
}

void add_element_as_recently_used_and_remove_last_recently_used(int memory_region_id)
{
    int move_to_next_index_value = memory_region_id;
    for (int index = 0; index < 5; index++)
    {
        int current_index_value = recent_used_memory_regions[index].value;
        recent_used_memory_regions[index].value = move_to_next_index_value;
        move_to_next_index_value = current_index_value;
    }
}

void move_element_to_recently_used_position(int index_found)
{
    int move_to_next_index_value = recent_used_memory_regions[index_found].value;
    for (int index = 0; index <= index_found; index++)
    {
        int current_index_value = recent_used_memory_regions[index].value;
        recent_used_memory_regions[index].value = move_to_next_index_value;
        move_to_next_index_value = current_index_value;
    }
}

int main()
{
    find(10);
    find(11);
    find(12);
    find(13);
    find(14);
    find(10);
    find(50);
}
