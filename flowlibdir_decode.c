#include <stdint.h>

struct flowlibdir_entry {
    char file_name[12];
    int32_t something;
    int32_t offset;
    int32_t size;
};

#include <stdio.h>
#include <string.h>

void flowlibdir(void) {
    FILE* fp;
    struct flowlibdir_entry entries[1000];
    int num_entries = 0;
    
    if((fp = fopen("flowlib.dir", "rb")) == NULL) {
        printf("can't open flowlib.dir\n");
        return;
    }

    int num_objs_read;

    int thing;

    num_objs_read = fread(&thing, 4, 1, fp);
    char c;
    while((c=getc(fp)) != EOF && num_entries <= 1000) {
        ungetc(c, fp);
        num_objs_read = fread(&entries[num_entries], 12, 1, fp);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for file name %s as expected:%d\n",
                   entries[num_entries].file_name,
                   num_objs_read);
        }

        num_objs_read = fread(&entries[num_entries].something, 4, 1, fp);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for something as expected:%d\n", num_objs_read);
        }

        num_objs_read = fread(&entries[num_entries].offset, 4, 1, fp);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for offset as expected:%d\n", num_objs_read);
        }

        num_objs_read = fread(&entries[num_entries].size, 4, 1, fp);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for size as expected:%d\n", num_objs_read);
        }

        num_entries++;
    }

    if(num_entries >= 1000) {
        printf("reached max entries\n");
    }

    printf("num_entries=%d\n", num_entries);
    printf("thing=%d\n", thing);
    int i;
    for(i = 0; i < num_entries; ++i) {
        printf("%s %d %d %d\n",
               entries[i].file_name,
               entries[i].something,
               entries[i].offset,
               entries[i].size);
        
    }
}
