/* crt0.cpp - Минимальный C++ runtime для xStep OS */

typedef unsigned long size_t;

/* Оператор new */
void* operator new(size_t size) {
    (void)size;
    return (void*)0;
}

void* operator new[](size_t size) {
    (void)size;
    return (void*)0;
}

/* Оператор delete */
void operator delete(void* ptr) {
    (void)ptr;
}

void operator delete[](void* ptr) {
    (void)ptr;
}

/* Обработчик pure virtual call */
extern "C" void __cxa_pure_virtual() {
    while (1) {
        __asm__ volatile("hlt");
    }
}

/* Заглушка для __cxa_atexit */
extern "C" void __cxa_atexit(void (*func)(void*), void* arg, void* dso) {
    (void)func;
    (void)arg;
    (void)dso;
}
