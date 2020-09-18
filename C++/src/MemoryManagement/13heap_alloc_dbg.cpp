

/*
//nSize = 256Bytes nNoMansLandSize = 4Bytes 

#define nNoMansLandSize 4
typedef struct _CrtMemBlockHeader{  //在debug模式下准备附加到所申请的内存之上的  所以在debug模式下分配的内存会比申请的内存大一些
    struct _CrtMemBlockHeader* pBlockHeaderNext;
    struct _CrtMemBlockHeader* pBlockHeaderPrev;
    char* szFileName;   //指向被调试文件的文件名
    int nLine;   //文件行
    size_t nDataSize;   //记录真正分配的大小
    int nBlockUse;  
    long IRequest;
    unsigned char gap[nNoMansLandSize];  //4个字符指针
}_CrtMemBlockHeader;


blockSize = sizeof(_CrtMemBlockHeader) + nSize + nNoMansLandSize; 
pHead = (_CrtMemBlockHeader*)_heap_alloc_base(blockSize);
if(_pFirstBlock)   //这两个指针将内存连接起来了
    _pFirstBlock->pBlockHeaderPrev = pHead;
    else 
    pLastBlock = pHead;

    //初始化_CrtMmemmBlockHeader结构体

    //link blocks together
    _pFirstBlock = pHead;
    static unsigned char _bNoMansLandFill = 0xf0;
    //fill in gap before and after real block
    memset((void*)pHead->gap, _bNoMansLandFill, nNoMansLandSize);
    memset((void*)(pbData(pHead) + nSize), _bNoMansLandFill, nNoMansLandSize);

    //fill data with silly value(but no-zero)
    memset((void*)pbData(pHead), _bCleanLandFill, nSize);
    return (void*)pbData(pHead);

    //调试模式下，所有经过Malloc分配的内存块都会用指针登记起来
    //利用CRT提供的指针，可以模拟调试器的功能}
*/
