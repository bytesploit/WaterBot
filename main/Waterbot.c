/*
 
 Copyright (c) 2017 Joel Parker
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is furnished
 to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 Early code inspired by the espressif example entitled tcp_udp_perf
 
 */

#include "Waterbot.h"
#include "ErrorHandling.h"
#include "UDPServer.h"
#include "Globals.h"

static char tag[]="waterbot";


// Event Loop Handler
esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            esp_wifi_connect();
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            ESP_LOGI(tag, "event_handler:SYSTEM_EVENT_STA_GOT_IP!");
            ESP_LOGI(tag, "got ip:%s\n",
                     ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
            // IP is availiable, start the UDP server
            udp_server();
            break;
        case SYSTEM_EVENT_AP_STACONNECTED:
            ESP_LOGI(tag, "station:" MACSTR " join,AID=%d\n",
                     MAC2STR(event->event_info.sta_connected.mac),
                     event->event_info.sta_connected.aid);
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
            ESP_LOGI(tag, "station:" MACSTR "leave,AID=%d\n",
                     MAC2STR(event->event_info.sta_disconnected.mac),
                     event->event_info.sta_disconnected.aid);
            break;
        default:
            break;
    }
    return ESP_OK;
}

void waterbot_task(void *pvParameter)
{
    // Set pins to output
    gpio_set_direction(RT_MOTOR_GPIO_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(RT_MOTOR_GPIO_2, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(LT_MOTOR_GPIO_3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LT_MOTOR_GPIO_4, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(WATER_GPIO_5, GPIO_MODE_OUTPUT);
    
     gpio_set_level(RT_MOTOR_GPIO_1,1); // off
     gpio_set_level(LT_MOTOR_GPIO_3,1); // off
    
    // Connect to the AP in STA mode
    tcpip_adapter_init();
    
    // Set Event Handler
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL) );
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    wifi_config_t sta_config = { };
    strcpy((char*)sta_config.sta.ssid, ssid);
    strcpy((char*)sta_config.sta.password, password);
    sta_config.sta.bssid_set = false;
    
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &sta_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );
    
    ESP_LOGI(tag, "connect to ap SSID:%s password:%s \n",
             ssid,password);
}

void app_main()
{
  //  xTaskCreate(&waterbot_task, "waterbot_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
    waterbot_task(NULL);
}
