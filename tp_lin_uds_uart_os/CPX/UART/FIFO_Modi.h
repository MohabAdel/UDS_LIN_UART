

#define FIFOSIZE   16         // size of the FIFOs (must be power of 2)
#define FIFOSUCCESS 1         // return value on success
#define FIFOFAIL    0         // return value on failure
typedef char txDataType;

void TxFifo_Init(void);

int TxFifo_Put(txDataType data);


int TxFifo_Get(txDataType *datapt);

unsigned short TxFifo_Size(void);

typedef char rxDataType;

void RxFifo_Init(void);

int RxFifo_Put(rxDataType data);

int RxFifo_Get(rxDataType *datapt);


unsigned short RxFifo_Size(void);


