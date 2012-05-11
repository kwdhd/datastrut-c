#ifndef MYBITSET_H
#define MYBITSET_H

#include <stdlib.h>
#include <limits.h>
#include <assert.h>



// ����һ�����α����Ƕ���λ
#define SIZE_T_BIT (CHAR_BIT*sizeof(size_t))
// �õ�һ��posλΪ1����λ��Ϊ0������
#define BISET_MASK(pos) (((size_t)1<<((pos)%SIZE_T_BIT))
// ���� pos ������bits�����е��Ǹ�Ԫ��
#define BISET_INDEX(set,pos) (set->bitarr[((pos)/SIZE_T_BIT)])
// ������Ҫ���ٸ� size_t ������ nbit
#define ARR_SIZE(nbits) (((bits)/SIZE_T_BIT)+1)

typedef struct MyBitSet{
    size_t *bitarr;
    size_t nbits;
}BitSet;

BitSet* BitSet_Init(size_t nbits)
{
    BitSet *bits = (BitSet*)calloc(sizeof(*BitSet));
    assert(bits);
    bits->bitarr = (size_t*)calloc(ARR_SIZE(nbits),sizeof(size_t));
    bits->nbits = nbits;
    
    return bits;
}

void BitSet_Free(BitSet* pbs)
{
    if( pbs == NULL)
        return;
    free(pbs->bitarr);
    free(pbs);
}
#endif


//
// 1 /**
// 2  * ��ʼ��һ��bitsetΪnbitsλ
// 3  */
// 4 bitset *bitset_init(size_t nbits)
// 5 {
// 6     bitset *set;
// 7 
// 8     set = malloc(sizeof(*set));
// 9     assert(set);
//10     //����ռ䲢��ʼ��Ϊ0.
//11     set->bits = calloc(BITSET_USED(nbits), sizeof(*set->bits));
//12     set->nbits = nbits;
//13 
//14     assert(set->bits);
//15 
//16     return set;
//17 }
//18 
//19 /**
//20  * ��set�е�����λ����Ϊ0
//21  */
//22 void bitset_reset(bitset * set)
//23 {
//24     memset(set->bits, 0, BITSET_USED(set->nbits) * sizeof(*set->bits));
//25 }
//26 
//27 //�ͷ�set
//28 void bitset_free(bitset * set)
//29 {
//30     free(set->bits);
//31     free(set);
//32 }
//33 
//34 //��posλ����Ϊ0.
//35 void bitset_clear_bit(bitset * set, size_t pos)
//36 {
//37     if (pos >= set->nbits)
//38     {
//39         SEGFAULT();
//40     }
//41 
//42     BITSET_WORD(set, pos) &= ~BITSET_MASK(pos);
//43 }
//44 //��posΪ����Ϊ1
//45 void bitset_set_bit(bitset * set, size_t pos)
//46 {
//47     if (pos >= set->nbits)
//48     {
//49         SEGFAULT();
//50     }
//51 
//52     BITSET_WORD(set, pos) |= BITSET_MASK(pos);
//53 }
//54 //����posλ���Ƿ���1
//55 int bitset_test_bit(bitset * set, size_t pos)
//56 {
//57     if (pos >= set->nbits)
//58     {
//59         SEGFAULT();
//60     }
//61 
//62     return (BITSET_WORD(set, pos) & BITSET_MASK(pos)) != 0;
//63 }
//64 
//
// Lighttpd�е�bit�Ӻϲ������Ͼ��������еĴ��붼�Ѿ��ڱ������������ˡ���Ȼ��ͷ�ļ��еĺ�������û��������������