

/*
typedef struct tagHeader{
    BITVEC  bitEntryHi;
  BITVEC  bitvEntryLo;
  BITVEC  bitvCommit;
    void*  pHeadpData;
  struct tagRegion* pRegion;  
}HEADER, *PHEADER;

int __cdecl __sbh_heap_init(void) {

    if(!(__sbh_pHeaderList = HeapAlloc(_crtheap, 0, 16 * sizeof(HEADER))))
        return false;

  __sbh_pHeaderScan = __sbh_pHeaderList;
  __sbh_pHeaderDefer = NULL;
  __sbh_cntHeaderList = 0;
  __sbh_sizeHeaderList = 16;
  
  return true;
}
*/
