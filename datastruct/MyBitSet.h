#ifndef MYBITSET_H
#define MYBITSET_H

#include <stdlib.h>
#include <limits.h>
#include <assert.h>



// 计算一个整形变量是多少位
#define SIZE_T_BIT (CHAR_BIT*sizeof(size_t))
// 得到一个pos位为1其它位置为0的掩码
#define BISET_MASK(pos) (((size_t)1<<((pos)%SIZE_T_BIT))
// 计算 pos 保存在bits数组中的那个元素
#define BISET_INDEX(set,pos) (set->bitarr[((pos)/SIZE_T_BIT)])
// 计算需要多少个 size_t 来保存 nbit
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
// 2  * 初始化一个bitset为nbits位
// 3  */
// 4 bitset *bitset_init(size_t nbits)
// 5 {
// 6     bitset *set;
// 7 
// 8     set = malloc(sizeof(*set));
// 9     assert(set);
//10     //分配空间并初始化为0.
//11     set->bits = calloc(BITSET_USED(nbits), sizeof(*set->bits));
//12     set->nbits = nbits;
//13 
//14     assert(set->bits);
//15 
//16     return set;
//17 }
//18 
//19 /**
//20  * 将set中的所有位重置为0
//21  */
//22 void bitset_reset(bitset * set)
//23 {
//24     memset(set->bits, 0, BITSET_USED(set->nbits) * sizeof(*set->bits));
//25 }
//26 
//27 //释放set
//28 void bitset_free(bitset * set)
//29 {
//30     free(set->bits);
//31     free(set);
//32 }
//33 
//34 //将pos位设置为0.
//35 void bitset_clear_bit(bitset * set, size_t pos)
//36 {
//37     if (pos >= set->nbits)
//38     {
//39         SEGFAULT();
//40     }
//41 
//42     BITSET_WORD(set, pos) &= ~BITSET_MASK(pos);
//43 }
//44 //将pos为设置为1
//45 void bitset_set_bit(bitset * set, size_t pos)
//46 {
//47     if (pos >= set->nbits)
//48     {
//49         SEGFAULT();
//50     }
//51 
//52     BITSET_WORD(set, pos) |= BITSET_MASK(pos);
//53 }
//54 //测试pos位置是否是1
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
// Lighttpd中的bit接合操作剪断精悍，所有的代码都已经在本文中贴出来了。当然，头文件中的函数声明没有贴出来。。。