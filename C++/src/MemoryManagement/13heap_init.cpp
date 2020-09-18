

/*Windows API 的部分代码*/
/*
int __cdecl _heap_init() {

//initialize the "big-block" heap first
    if((_crtheap = HeapCreat(mtflag ? 0 : HEAP_NO_SERIALIZE, BYTES_PER_PAGE, 0)) == NULL)
          return 0;

    if(_sbh_heap_init() == 0) {
        HeapDestory(_crtheap); 
        return 0;
    }
    return 1;
}
 */
