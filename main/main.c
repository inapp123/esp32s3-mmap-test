#include <stdio.h>
#include "esp_partition.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <inttypes.h>


const char *TAG = "main";


void app_main(void)
{

    const esp_partition_t* part = esp_partition_find_first(0x40, 0x00, "asset");
    if (part == NULL) {
        ESP_LOGE(TAG, "Failed to find asset partition");
        abort();
    }    
    spi_flash_mmap_dump();
    ESP_LOGI(TAG, "Found asset partition at offset 0x%" PRIx32 " with size %" PRIx32, part->address,part->size);


    uint8_t* mmaped_ptr;
    spi_flash_mmap_handle_t handle;
    ESP_ERROR_CHECK(esp_partition_mmap(part, 0, part->size, SPI_FLASH_MMAP_DATA, &(mmaped_ptr),&handle));
    ESP_LOGI(TAG, "Mounted at offset 0x%" PRIx32 "", (uint32_t)mmaped_ptr);

    while (1)
    {
        printf("hello world!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}