// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) {
    BitLen = len;
    MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField& bf) {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const {
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const {
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const {
    return BitLen;
}

void TBitField::SetBit(const int n) {
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const {
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField& bf) {
    if (*this == bf) return *this;
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const {
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const {
    if (*this == bf) return 0;
    return 1;
}

TBitField TBitField::operator|(const TBitField& bf) {
    TBitField res(max(BitLen,bf.BitLen));
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < BitLen; i++) res.pMem[i] = pMem[i] | bf.pMem[i];
    }   
    else if (BitLen > bf.BitLen){
        int dif = BitLen - bf.BitLen;
        for (int i = 0; i < dif; i++) res.pMem[i] = pMem[i];
        for (int i = dif; i < BitLen; i++) res.pMem[i] = pMem[i] | bf.pMem[i];
    }
    else {
        int dif = bf.BitLen - BitLen;
        for (int i = 0; i < dif; i++) res.pMem[i] = bf.pMem[i];
        for (int i = dif; i < bf.BitLen; i++) res.pMem[i] = pMem[i] | bf.pMem[i];
    }

    return res;
}

TBitField TBitField::operator&(const TBitField& bf) {
    TBitField res(max(BitLen, bf.BitLen));
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < BitLen; i++) res.pMem[i] = pMem[i] & bf.pMem[i];
    }
/*    else if (BitLen > bf.BitLen) {
        int dif = BitLen - bf.BitLen;
        for (int i = 0; i < dif; i++) res.pMem[i] = pMem[i];
        for (int i = dif; i < BitLen; i++) res.pMem[i] = pMem[i] | bf.pMem[i];
    }
    else {
        int dif = bf.BitLen - BitLen;
        for (int i = 0; i < dif; i++) res.pMem[i] = bf.pMem[i];
        for (int i = dif; i < bf.BitLen; i++) res.pMem[i] = pMem[i] | bf.pMem[i];
 */   

    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~pMem[i];
    }
    return FAKE_BITFIELD;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    return ostr;
}