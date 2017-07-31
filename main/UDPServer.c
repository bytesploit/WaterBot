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

#include "UDPServer.h"
#include "ErrorHandling.h"
#include "Globals.h"

static char tag[]="udpserver";
int mysocket;

// UDP Listener
esp_err_t udp_server()
{
    struct sockaddr_in si_other;
    
    unsigned int slen = sizeof(si_other),recv_len;
    char buf[BUFLEN];
    
    // bind to socket
    ESP_LOGI(tag, "bind_udp_server port:%d", PORT_NUMBER);
    mysocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mysocket < 0) {
        show_socket_error_reason(mysocket);
        return ESP_FAIL;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUMBER);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(mysocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        show_socket_error_reason(mysocket);
        close(mysocket);
        return ESP_FAIL;
    } else {
        ESP_LOGI(tag,"socket created without errors");
        
        while(1)
        {
            ESP_LOGI(tag,"Waiting for incoming data");
            memset(buf,0,BUFLEN);
            
            if ((recv_len = recvfrom(mysocket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
            {
                ESP_LOGE(tag,"recvfrom");
                break;
            }
            
            ESP_LOGI(tag,"Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
            ESP_LOGI(tag,"Data: %s -- %d\n" , buf, recv_len);
            
            // Set the NULL byte to avoid garbage in the read buffer
            if ((recv_len + 1) < BUFLEN)
                buf[recv_len + 1] = '\0';
            
            // Valid Commands: forward, reverse, right, left, zeroRight, zeroLeft, valveOn, valveOff, stop
            
            // Note: speed is inverse polarity
            if ( memcmp( buf, "forward", recv_len) == 0) {
                ESP_LOGI(tag,"Inside Forward Case\n");
                // rt motor, speed 0 (On), direction 1 (Forward)
                gpio_set_level(RT_MOTOR_GPIO_1,0);
                gpio_set_level(RT_MOTOR_GPIO_2,1);
                
                // lt motor, speed 0,(On), direction 1 (Forward)
                gpio_set_level(LT_MOTOR_GPIO_3,0);
                gpio_set_level(LT_MOTOR_GPIO_4,1);
                
            } else if ( memcmp( buf, "reverse", recv_len) == 0) {
                ESP_LOGI(tag,"Inside Reverse Case\n");
                // rt motor, speed 0 (On), direction 0 (Reverse)
                gpio_set_level(RT_MOTOR_GPIO_1,0);
                gpio_set_level(RT_MOTOR_GPIO_2,0);
                
                // lt motor, speed 0,(On), direction 0 (Reverse)
                gpio_set_level(LT_MOTOR_GPIO_3,0);
                gpio_set_level(LT_MOTOR_GPIO_4,0);
                
            } else if ( memcmp( buf, "right", recv_len) == 0) {
                ESP_LOGI(tag,"Inside Right Case\n");
                // rt motor, speed 0 (On), direction 1 (Forward)
                gpio_set_level(RT_MOTOR_GPIO_1,0);
                gpio_set_level(RT_MOTOR_GPIO_2,1);
                
                // lt motor, speed 1,(Off)
                gpio_set_level(LT_MOTOR_GPIO_3,1);
                
            } else if ( memcmp( buf, "left", recv_len) == 0) {
                ESP_LOGI(tag,"Inside Left Case\n");
                // rt motor, speed 1 (Off)
                gpio_set_level(RT_MOTOR_GPIO_1,1);
                
                // lt motor, speed 0,(On), direction 1 (Forward)
                gpio_set_level(LT_MOTOR_GPIO_3,0);
                gpio_set_level(LT_MOTOR_GPIO_4,1);
                
            } else if ( memcmp( buf, "zeroRight", recv_len) == 0) {
                ESP_LOGI(tag,"Inside zeroRight Case\n");
                // rt motor, speed 0 (On), direction 1 (Forward)
                gpio_set_level(RT_MOTOR_GPIO_1,0);
                gpio_set_level(RT_MOTOR_GPIO_2,1);
                
                // lt motor, speed 0,(On), direction 0 (Reverse)
                gpio_set_level(LT_MOTOR_GPIO_3,0);
                gpio_set_level(LT_MOTOR_GPIO_4,0);
                
            } else if ( memcmp( buf, "zeroLeft", recv_len) == 0) {
                ESP_LOGI(tag,"Inside zeroLeft Case\n");
                // rt motor, speed 0 (On), direction 0 (Reverse)
                gpio_set_level(RT_MOTOR_GPIO_1,0);
                gpio_set_level(RT_MOTOR_GPIO_2,0);
                
                // lt motor, speed 0,(On), direction 1 (Forward)
                gpio_set_level(LT_MOTOR_GPIO_3,0);
                gpio_set_level(LT_MOTOR_GPIO_4,1);
                
            }  else if ( memcmp( buf, "valveOn", recv_len) == 0) {
                ESP_LOGI(tag,"Inside valveOn Case\n");
                // water valve 1 (on)
                gpio_set_level(WATER_GPIO_5,1);
                
            }  else if ( memcmp( buf, "valveOff", recv_len) == 0) {
                ESP_LOGI(tag,"Inside valveOff Case\n");
                // water valve 0 (off)
                gpio_set_level(WATER_GPIO_5,0);
                
            }  else if ( memcmp( buf, "stop", recv_len) == 0) {
                 ESP_LOGI(tag,"Inside Stop Case\n");
                // water valve 0 (off)
                gpio_set_level(WATER_GPIO_5,0);
                
                // rt motor speed 1 (off)
                gpio_set_level(RT_MOTOR_GPIO_1,1);
                
                // lt motor speed 1 (off)
                gpio_set_level(LT_MOTOR_GPIO_3,1);
                
            } else {
                ESP_LOGE(tag,"Command: %s\n", buf);
            }
        }
        
        close(mysocket);
        return ESP_FAIL;
    }
    return ESP_OK;
}
