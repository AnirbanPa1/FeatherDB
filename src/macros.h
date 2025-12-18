#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

#define ID_SIZE sizeof(((Row *)0)->id)
#define USERNAME_SIZE sizeof(((Row *)0)->username)
#define EMAIL_SIZE sizeof(((Row *)0)->email)

#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)