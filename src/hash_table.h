struct Item{
    char* key;
    char* value;
};

struct HasTable{
    int size;
    int count;
    Item** items;
};