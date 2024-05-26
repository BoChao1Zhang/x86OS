__asm__(".code16gcc");
#include "loader.h"

static boot_info_t boot_info;



static void show_msg(const char* msg){
    char c;

    while((c = *msg++ )!='\0'){
        asm volatile(
            "mov $0xe,%%ah\n\t"
            "mov %[ch],%%al\n\t"
            "int $0x10"::[ch]"r"(c)
        );
    }
}



/**
 * @brief 检测内存
 * 
 * 此函数用于检测系统的内存情况。
 * 它通过调用BIOS中断0x15来获取系统的内存映射信息，并将有效的内存区域保存到boot_info结构中。
 * 
 * @note 此函数是静态函数，仅在当前文件中可见。
 */
static void detect_memory(void){

    SMAP_entry_t SMAP_entry;
    show_msg("try to detect memory");

    uint32_t contID = 0;
    int signature,bytes;

    boot_info.ram_region_count = 0;
    for(int i =0;i< BOOT_RAM_REGION_MAX;i++){
        SMAP_entry_t *entry = &SMAP_entry;

        asm volatile("int $0x15"
        :"=a"(signature),"=c"(bytes),"=b"(contID)
        :"a"(0xE820),"b"(contID),"c"(24),"d"(0x534D4150),"D"(entry));

        if(signature != 0x534D4150 ){
            show_msg("failed\r\n");
            return;
        }

        if(bytes > 20 &&(entry->ACPI & 0x0001) == 0){
            continue;
        }

        if(entry->Type == 1){
            boot_info.ram_region_cfg[boot_info.ram_region_count].start = entry->BaseL;
            boot_info.ram_region_cfg[boot_info.ram_region_count].size = entry->LengthL;

            boot_info.ram_region_count++;
        }

        if(contID ==0){
            break;
        }
    }
}


void loader_entry(void){
    show_msg("....loading.....");
    for(;;){}
}
