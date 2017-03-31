#include <stdint.h>

struct flowlibdir_entry {
    char file_name[13];
    int32_t something;
    int32_t offset;
    int32_t size;
};

#include <stdio.h>
#include <string.h>

void flowlibdir(void) {
    FILE* flowlibdir;
    FILE* flowliblib;
    char file_buff[1024*1024*6];//6MB file buffer, bigger than whole flowlib.lib file
    struct flowlibdir_entry entries[1000];
    int num_entries = 0;

    //does it matter if I pass b for binary to fopen?
    if((flowlibdir = fopen("flowlib.dir", "rb")) == NULL) {
        printf("can't open flowlib.dir\n");
        return;
    }

    if((flowliblib = fopen("flowlib.lib", "rb")) == NULL) {
        printf("can't open flowlib.lib\n");
    }

    int num_objs_read;

    int thing;

    num_objs_read = fread(&thing, 4, 1, flowlibdir);
    char c;

    //change to fread num_things directly to entries array?
    //if still need to see if at end of file, maybe instead of getc==eof use
    //if fread returns zero bytes read?
    //can have fread return num bytes read by saying size is 1, num objects is num bytes
    while((c=getc(flowlibdir)) != EOF && num_entries <= 1000) {
        ungetc(c, flowlibdir);
        num_objs_read = fread(&entries[num_entries], 12, 1, flowlibdir);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for file name %s as expected:%d\n",
                   entries[num_entries].file_name,
                   num_objs_read);
        }
        entries[num_entries].file_name[12] = '\0';

        num_objs_read = fread(&entries[num_entries].something, 4, 1, flowlibdir);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for something as expected:%d\n", num_objs_read);
        }

        num_objs_read = fread(&entries[num_entries].offset, 4, 1, flowlibdir);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for offset as expected:%d\n", num_objs_read);
        }

        num_objs_read = fread(&entries[num_entries].size, 4, 1, flowlibdir);
        if(num_objs_read != 1) {
            printf("didn't get 1 object for size as expected:%d\n", num_objs_read);
        }

        if(flowliblib) {
            FILE* extracted_file;
        
            if((extracted_file = fopen(entries[num_entries].file_name, "wb")) != NULL) {
                //get the file out of flowlib.lib
                if(fread(file_buff, entries[num_entries].size, 1, flowliblib) != 1) {
                    printf("didn't get 1 object extracted from flowlib.lib for %s\n",
                           entries[num_entries].file_name);
                }
                
                //write to the file
                if(fwrite(file_buff, entries[num_entries].size, 1, extracted_file) != 1) {
                    printf("didn't write 1 object of extracted file %s\n",
                           entries[num_entries].file_name);
                }
            }
            else {
                printf("could not open file %s to write to\n", entries[num_entries].file_name);
            }

            fclose(extracted_file);
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
