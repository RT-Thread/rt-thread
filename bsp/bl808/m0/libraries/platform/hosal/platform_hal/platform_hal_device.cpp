/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <platform_hal_device.h>

extern "C" void* operator new(size_t size) 
{
    /* printf("[C++] new %d\r\n", size); */
    return pvPortMalloc(size); 
}

extern "C" void* operator new[](size_t size) 
{
    /* printf("[C++] new[] %d\r\n", size); */
    return pvPortMalloc(size); 
}

extern "C" void operator delete(void* ptr) {
    /* printf("[C++] delete %p\r\n", ptr); */
    vPortFree(ptr);
}

extern "C" void operator delete[](void* ptr) {
    /* printf("[C++] delete[] %p\r\n", ptr); */
    vPortFree(ptr);
}

BLLinkedItem::BLLinkedItem() 
{
    this->next = NULL;
}

BLLinkedItem* BLLinkedItem::attach(class BLLinkedItem &item)
{
    /*assert when next is NOT NULL*/
    if (this->next) {
        printf("[ERR] next is NOT NULL. %p -->> %p\r\n", this->next, &item);
        return NULL;
    } else if (this == &item) {
        printf("[ERR] linked to self. %p -->> %p\r\n", this, &item);
        return NULL;
    }
    this->next = &item;
    return this;
}

BLLinkedItem* BLLinkedItem::detach()
{
    BLLinkedItem *tmp;

    tmp = this->next;
    this->next = NULL;

    return tmp;
}

BLLinkedList::BLLinkedList() 
{
    this->head = NULL;
    this->tail = NULL;
}

BLLinkedList* BLLinkedList::push(class BLLinkedItem &item) 
{
    printf("[BLLinkedList] push %p\r\n", &item);

    if (NULL == this->head) {
        printf("new push\r\n");
        this->head = &item;
        this->tail = &item;
        return this;
    }
    /*tail should NOT be NULL, assert here if tail is NULL?*/
    printf("continue push\r\n");
    if (NULL == this->tail->attach(item)) {
        return NULL;
    }
    this->tail = &item;

    return this;
}

BLLinkedItem* BLLinkedList::pop() 
{
    BLLinkedItem *item;

    if (NULL == this->head) {
        printf("NULL HEAD\r\n");
        return NULL;
    }
    item = this->head;
    this->head = item->detach();

    printf("[POP] POP %p\r\n", item);

    return item;
}

BLAesRequest::BLAesRequest()
{
    memset(this->key, 0, sizeof(this->key));
    memset(this->iv, 0, sizeof(this->iv));
    this->src = NULL;
    this->dst = NULL;
    this->len = 0;
    this->first_use = 0;
}

BLAesRequest::BLAesRequest(uint8_t *key, uint8_t *iv, uint8_t *src, uint8_t *dst, int len)
{
    memcpy(this->key, key, sizeof(this->key));
    if (iv) {
        memcpy(this->iv, iv, sizeof(this->iv));
    }
    this->src = src;
    this->dst = dst;
    this->len = len;
    this->first_use = 0;
}

int BLAesRequest::done_pre(int use_encryption)
{
    this->task_handle = xTaskGetCurrentTaskHandle();
    this->done = 0;
    this->is_encryption = use_encryption;

    return 0;
}

int BLAesRequest::done_wait()
{
    while (0 == this->done) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
    return 0;
}

int BLAesRequest::done_set()
{
    this->done = 1;
    xTaskNotifyGive(this->task_handle);

    return 0;
}

int BLAesRequest::done_set_auto()
{
    this->done = 1;
    //TODO 
    printf("[C++] [%s] ongoing...\r\n", __PRETTY_FUNCTION__);

    return 0;
}

int BLAesRequest::done_set_FromISR()
{
    BaseType_t xHigherPriorityTaskWoken;

    this->done = 1;
    vTaskNotifyGiveFromISR(this->task_handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    return 0;
}

int BLAesEngine::encryption(BLAesRequest &req)
{
    printf("%s %p...\r\n", __PRETTY_FUNCTION__, &req);

    /*request prepare*/
    req.done_pre(1);
    /*push to queue and trigger if necessary*/
    if (NULL == this->push(req)) {
        return -1;
    }
    this->encryption_trigger();
    /*request wait*/
    req.done_wait();

    return 0;
}

void BLAesEngine::encryption_trigger()
{
    /*Trigger SOFTIRQ if necessary*/
    return;
}

void BLAesEngine::decryption_trigger()
{
    /*Trigger SOFTIRQ if necessary*/
    return;
}

int BLAesEngine::decryption(BLAesRequest &req)
{
    printf("%s %p...\r\n", __PRETTY_FUNCTION__, &req);

    /*request prepare*/
    req.done_pre(0);
    /*push to queue and trigger if necessary*/
    if (NULL == this->push(req)) {
        return -1;
    }
    this->decryption_trigger();
    /*request wait*/
    req.done_wait();

    return 0;
}

static class BLAesEngine *aes_engine;
extern "C" int platform_hal_device_init(void)
{
    class BLAesRequest *aes_request = new BLAesRequest[6];
    aes_engine = new BLAesEngine();

    (void)aes_request;
#if 0
    aes_engine->encryption(aes_request[0]);
#endif

    return 0;
}
