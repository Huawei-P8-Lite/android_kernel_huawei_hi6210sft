/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafStdlib.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��5��25��
  ����޸�   :
  ��������   : TafStdlib.C�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��23��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "pslog.h"
#include "TafStdlib.h"
#include "MnErrorCode.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
#include "MnMsgApi.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
/* Add by j00174725 for IOT Test(DTS2015031908232), 2015-03-23, Begin */
#include "MnCallApi.h"
/* Add by j00174725 for IOT Test(DTS2015031908232), 2015-03-23, End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_STD_LIB_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/
/* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
LOCAL VOS_UINT8 f_aucMsgAsciiSfxDefAlpha[TAF_STD_MAX_GSM7BITDEFALPHA_NUM] =
{
    '@',  163,   '$',  165,  232,  233,  249,  236,  242,  199,  0x0a, 216,  248,  0x0d, 197,  229,
    0xff, '_',   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 198,  230,  223,  201,
    ' ',  '!',   '"',  '#',  164,  '%',  '&',  0x27, '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
    '0',  '1',   '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    161,  'A',   'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
    'P',  'Q',   'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  196,  214,  209,  220,  167,
    191,  'a',   'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
    'p',  'q',   'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  228,  246,  241,  252,  224
};
/* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_STD_Itoa
 ��������  : ������ת��ΪASCII��, �����������ַ���
 �������  : VOS_UINT32                          ulDigit            - ��ת��ΪASCII�������
 �������  : VOS_CHAR                           *pcDigitStr         - ���������ַ���
             VOS_UINT32                         *pulDigitStrLength  - ���������ַ�������
 �� �� ֵ  : VOS_FALSE  - ת��ʧ��
             VOS_TRUE   - ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_STD_Itoa(
    VOS_UINT32                          ulDigit,
    VOS_CHAR                           *pcDigitStr,
    VOS_UINT32                         *pulDigitStrLength
)
{
    VOS_INT32                           lCharNum;

    lCharNum = sprintf(pcDigitStr, "%d", (VOS_INT)ulDigit);

    *pulDigitStrLength = (VOS_UINT32)lCharNum;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_AsciiNum2HexString
 ��������  : ���16�����ַ���ת������
 �������  : pucSrc                          - ��ת��ΪASCII�������
 �������  : pucSrc                          - ת���������
 �� �� ֵ  : VOS_FALSE  - ת��ʧ��
             VOS_TRUE   - ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 TAF_STD_AsciiNum2HexString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                         *pusSrcLen
)
{
    VOS_UINT16                          usChkLen;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           ucLeft;
    VOS_UINT16                          usSrcLen;
    VOS_UINT8                          *pucDst = VOS_NULL_PTR;

    usChkLen        = 0;
    ucTmp           = 0;
    ucLeft          = 0;
    usSrcLen        = *pusSrcLen;
    pucDst          = pucSrc;

    /* ��������������ֽ��򷵻ش��� */
    if (0 != (usSrcLen % 2))
    {
        return VOS_FALSE;
    }

    while (usChkLen < usSrcLen)
    {
        /* the number is 0-9 */
        if(isdigit(pucSrc[usChkLen]))
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        /* the number is a-f */
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') )
        {
            ucLeft = (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        /* the number is A-F */
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') )
        {
            ucLeft = (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return VOS_FALSE;
        }

        pucDst[ucTmp] = 0xf0 & (ucLeft << 4);
        usChkLen += 1;

        /* the number is 0-9 */
        if(isdigit(pucSrc[usChkLen]))
        {
            pucDst[ucTmp] |= pucSrc[usChkLen] - '0';
        }
        /* the number is a-f */
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') )
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        /* the number is A-F */
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') )
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return VOS_FALSE;
        }

        usChkLen += 1;
        ucTmp += 1;
    }

    *pusSrcLen = usSrcLen / 2;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_HexAlpha2AsciiString
 ��������  : ���16�����ַ���ת������
 �������  : pucSrc                          - ��ת��ΪASCII�������
             usSrcLen                        - ��ת��ΪASCII������ֳ���
 �������  : pucDst                          - ת�����ASCII��
 �� �� ֵ  : ת�����ASCII�볤��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_STD_HexAlpha2AsciiString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    VOS_UINT8                          *pucDst
)
{
    VOS_UINT16                          usLen;
    VOS_UINT16                          usChkLen;
    VOS_UINT8                           ucHigh;
    VOS_UINT8                           ucLow;
    VOS_UINT8                          *pucWrite = VOS_NULL_PTR;
    VOS_UINT8                          *pucRead = VOS_NULL_PTR;

    pucWrite = pucDst;
    pucRead  = pucSrc;
    usLen    = 0;
    usChkLen = 0;
    ucHigh   = 0;
    ucLow    = 0;

    /* ɨ�������ִ� */
    /*lint -e961*/
    while ( usChkLen++ < usSrcLen )
    {
        ucHigh = 0x0F & (*pucRead >> 4);
        ucLow  = 0x0F & *pucRead;

        usLen += 2;    /* ��¼���� */

        if (0x09 >= ucHigh)   /* 0-9 */
        {
            *pucWrite++ = ucHigh + 0x30;
        }
        else if (0x0A <= ucHigh)    /* A-F */
        {
            *pucWrite++ = ucHigh + 0x37;
        }
        else
        {

        }

        if (0x09 >= ucLow)   /* 0-9 */
        {
            *pucWrite++ = ucLow + 0x30;
        }
        else if (0x0A <= ucLow)    /* A-F */
        {
            *pucWrite++ = ucLow + 0x37;
        }
        else
        {

        }

        /* ��һ���ַ� */
        pucRead++;
    }
    /*lint +e961*/

    return usLen;
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/* MN_UnPack7Bit��MnMsgDecode.c�Ƶ����ļ�������ΪTAF_STD_UnPack7Bit */
/* MN_Pack7Bit��MnMsgEncode.c�Ƶ����ļ�������ΪTAF_STD_Pack7Bit */

/*****************************************************************************
 �� �� ��  : TAF_STD_UnPack7Bit
 ��������  : ͬ������,��7bit���뷽ʽ���ַ�ת��Ϊ8bit�ַ�
 �������  : pucOrgChar            - ָ����Ҫת�����ַ�ָ��
             ulLen                 - ��Ҫת�����ַ����ȣ�7λλ�����
             ucFillBit             - ��Ҫ����Bit����
 �������  : pucUnPackedChar       - ָ��ת�����ָ��
             pulLen                - ָ��ת������ַ����ȣ�8λλ�����
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_UINT32  TAF_STD_UnPack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucUnPackedChar
)
{
    /*����ֽڵ�ַ*/
    VOS_UINT32                          ulPos = 0;
     /*���λƫ��*/
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulLoop;

    if ((VOS_NULL_PTR == pucOrgChar)
     || (VOS_NULL_PTR == pucUnPackedChar))
    {
        return VOS_ERR;
    }

    /*����Э��23040 9.2.3.24 UDHL��UDH������Fill Bits��SM��ȥ��Fill Bits�����SM(Unit: Septet),���Ի��SM�а����ַ�����*/
    ulOffset = ucFillBit % 8;

    /*��һ�����Ƴ���ǰ��Ч��ƫ��λulOffset���õ��ַ��ĵ�(8 - ulOffset)λ��
      �ڶ�������(8 - ulOffset)С��7λ����Ҫ����һ��OCTET�л�ȡ��(7 - (8 - ulOffset))λ
      ����������ȡ��һ������Դ���±�(ulPos)����Ҫȥ��������λ(ƫ��λulOffset)*/
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        pucUnPackedChar[ulLoop] = (VOS_UINT8)(pucOrgChar[ulPos] >> ulOffset);
        if (ulOffset > 1)
        {
            /*lint -e701*/
            pucUnPackedChar[ulLoop] |= (VOS_UINT8)((pucOrgChar[ulPos + 1UL] << (8 - ulOffset)) & TAF_STD_7BIT_MASK);
            /*lint +e701*/
        }
        else
        {
            pucUnPackedChar[ulLoop] &= TAF_STD_7BIT_MASK;
        }

        ulPos   += (ulOffset + 7) / 8;
        ulOffset = (ulOffset + 7) % 8;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_Pack7Bit
 ��������  : ͬ������,���ַ�ת��Ϊ7bit���뷽ʽ
 �������  : pucOrgChar          - ָ����Ҫת�����ַ�ָ��
             ulLen               - ��Ҫת�����ַ����ȣ���λseptet ע��:����Ԫ�ؽ���7bit��Ч����Ȼռ��1OCTET���ڴ�ռ�
             ucFillBit           - ��Ҫ����Bit����
 �������  : pucPackedChar       - ָ��ת�����ָ��
             pulLen              - ָ��ת������ַ����ȣ���λoctet
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_UINT32  TAF_STD_Pack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucPackedChar,
    VOS_UINT32                          *pulLen
)
{
    /*����ֽڵ�ַ*/
    VOS_UINT32                          ulPos = 0;
    /*���λƫ��*/
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulLoop;

    if ((VOS_NULL_PTR == pucOrgChar)
     || (VOS_NULL_PTR == pucPackedChar)
     || (VOS_NULL_PTR == pulLen))
    {
        return VOS_ERR;
    }

    *pulLen = (VOS_UINT32)((((ulLen * 7) + ucFillBit) + 7) / 8);

    ulOffset = ucFillBit % 8;

    /*bit 7   6   5   4   3   2   1   0 */
    /*    |digit1L|   |---ulOffset1---| */ /*����ulOffset1λ*/
    /*                |(0)  digit1H   | */ /*����(8-ulOffset1λ)*/
    /*    |-digit2L-  |   |-ulOffset2-| */ /*ƫ����Ϊ(8-1+ulOffset1)%8*/

    /*��һ�����ճ���ǰ�Ѿ�����ƫ��λulOffset����������Դ��ȡ��һ��OCTET����(8 - ulOffset)λ��
      �ڶ�������(8 - ulOffset)С��7λ����Ҫ����ǰ����Դ�ַ����¸�(7 - (8 - ulOffset))λ��䵽Ŀ�����ݵ���һ��OCTET��
      ����������ȡ��һ��Ŀ�����ݵ��±�(ulPos)���Ѿ���������λ(ƫ��λulOffset)*/
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        if ((pucOrgChar[ulLoop] & (~TAF_STD_7BIT_MASK)) != 0)
        {
            return VOS_ERR;
        }

        pucPackedChar[ulPos] |= (VOS_UINT8)((VOS_UINT32)(pucOrgChar[ulLoop] & TAF_STD_7BIT_MASK) << ulOffset);
        if (ulOffset > 1)
        {
            pucPackedChar[ulPos + 1UL] = (VOS_UINT8)((pucOrgChar[ulLoop] & TAF_STD_7BIT_MASK) >> (8 - ulOffset));
        }

        ulPos   += (ulOffset + 7) / 8;
        ulOffset = (ulOffset + 7) % 8;
    }

    return VOS_OK;
}
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdNumberToAscii
 ��������  : ��BCD����ĺ���ת����Ascii����ĺ���
 �������  : pBcdNumber     - BCD����
             ucBcdLen       - BCD����ĳ���
 �������  : pcAsciiNumber  - ת���õ���ASCII����(��'\0'��β)
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdNumberToAscii(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                           *pcAsciiNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pcAsciiNumber))
    {
        return MN_ERR_NULLPTR;
    }

    /*���������ַ�����ȥ����Ч��0XFF����*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*�ж�pucBcdAddress��ָ����ַ��������һ���ֽڵĸ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*��������*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*�жϵ�ǰ�����������λ���뻹��ż��λ���룬��0��ʼ����ż��*/
        if (1 == (ucLoop % 2))
        {
            /*���������λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*�����ż��λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*������������ת����Ascii����ʽ*/
        ulRet = TAF_STD_ConvertBcdCodeToAscii(ucBcdCode, &(pcAsciiNumber[ucLoop]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }

    pcAsciiNumber[ucLoop] = '\0';      /*�ַ���ĩβΪ0*/

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdCodeToAscii
 ��������  : ��BCD������ַ�ת����Ascii���ַ�
 �������  : ucBcdCode   - BCD������ַ�
 �������  : pcAsciiCode - ת���õ���ASCII���ַ�
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdCodeToAscii(
    VOS_UINT8                           ucBcdCode,
    VOS_CHAR                           *pcAsciiCode
)
{
    VOS_CHAR                            cAsciiCode;

    if (VOS_NULL_PTR == pcAsciiCode)
    {
        return MN_ERR_NULLPTR;
    }

    if (ucBcdCode <= 0x09)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x30);
    }
    else if (0x0A == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x20);    /*�ַ�'*'*/
    }
    else if (0x0B == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x18);    /*�ַ�'#'*/
    }
    else if ((0x0C == ucBcdCode)
          || (0x0D == ucBcdCode)
          || (0x0E == ucBcdCode))
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x55);    /*�ַ�'a', 'b', 'c'*/
    }
    else
    {
        return MN_ERR_INVALID_BCD;
    }

    *pcAsciiCode = cAsciiCode;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiNumberToBcd
 ��������  : ��Ascii����ĺ���ת����BCD����ĺ���
 �������  : pcAsciiNumber - ��'\0'��β��ASCII�ַ�����
 �������  : pucBcdNumber   - ת���õ���BCD����
             pucBcdLen      - ת���õ���BCD����ĳ���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertAsciiNumberToBcd(
    const VOS_CHAR                     *pcAsciiNumber,
    VOS_UINT8                          *pucBcdNumber,
    VOS_UINT8                          *pucBcdLen
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pcAsciiNumber)
     || (VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pucBcdLen))
    {
        return MN_ERR_NULLPTR;
    }

    for (ucLoop = 0; pcAsciiNumber[ucLoop] != '\0'; ucLoop++)
    {
        ulRet = TAF_STD_ConvertAsciiCodeToBcd(pcAsciiNumber[ucLoop], &ucBcdCode);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /*����ǰ��Ҫ����Ŀռ���0*/
        pucBcdNumber[(ucLoop / 2)] &= ((ucLoop % 2) == 1) ? 0x0F : 0xF0;

        /*������������Ӧ�Ŀռ�*/
        pucBcdNumber[(ucLoop / 2)] |= (((ucLoop % 2) == 1) ? ((ucBcdCode << 4) & 0xF0) : (ucBcdCode & 0x0F));
    }

    /*�������Ϊ�����������һ���ַ���Ҫ�� F */
    if (1 == (ucLoop % 2))
    {
        pucBcdNumber[(ucLoop / 2)] |= 0xF0;
    }

    *pucBcdLen = (ucLoop + 1) / 2;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiAddrToBcd
 ��������  : ͬ������,��MN_MSG_ASCII_ADDR_STRU���͵�ַת����MN_MSG_BCD_ADDR_STRU���͵�ַ
 �������  : pstAsciiAddr   - MN_MSG_ASCII_ADDR_STRU���͵�ַ
 �������  : pstBcdAddr     - MN_MSG_BCD_ADDR_STRU���͵�ַ
 �� �� ֵ  : MN_ERR_NO_ERRORת�������ɹ�������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��13��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_STD_ConvertAsciiAddrToBcd(
    MN_MSG_ASCII_ADDR_STRU             *pstAsciiAddr,
    MN_MSG_BCD_ADDR_STRU               *pstBcdAddr
)
{
    VOS_UINT32 ulRet;

    if ((VOS_NULL_PTR == pstAsciiAddr)
     || (VOS_NULL_PTR == pstBcdAddr))
    {
        return MN_ERR_NULLPTR;
    }

    MN_GET_ADDRTYPE(pstBcdAddr->addrType,
                    pstAsciiAddr->enNumType,
                    pstAsciiAddr->enNumPlan);

    ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)(pstAsciiAddr->aucAsciiNum),
                              pstBcdAddr->aucBcdNum,
                              &pstBcdAddr->ucBcdLen);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiCodeToBcd
 ��������  : ��Ascii���ַ�ת����BCD���ַ�
 �������  : ucAsciiCode  - ASCII�ַ�
 �������  : pucBcdCode   - ת���õ���BCD��
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertAsciiCodeToBcd(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                          *pucBcdCode
)
{
    if (VOS_NULL_PTR == pucBcdCode)
    {
        return MN_ERR_NULLPTR;
    }

    if ((cAsciiCode >= '0')
     && (cAsciiCode <= '9'))
    {
        *pucBcdCode = (VOS_UINT8)(cAsciiCode - '0');
    }
    else if ('*' == cAsciiCode)
    {
        *pucBcdCode = 0x0a;
    }
    else if ('#' == cAsciiCode)
    {
        *pucBcdCode = 0x0b;
    }
    else if (('a' == cAsciiCode)
          || ('b' == cAsciiCode)
          || ('c' == cAsciiCode))
    {
        *pucBcdCode = (VOS_UINT8)((cAsciiCode - 'a') + 0x0c);
    }
    else
    {
        return MN_ERR_INVALID_ASCII;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertDeciDigitToBcd
 ��������  : ��ʮ��������ת����BCD��
 �������  : ucDeciDigit ʮ��������
             bReverseOrder TAF_TRUE����ת��,��BCD��ĸ�4BIT��Ӧʮ���Ƶĸ�λ;
                           TAF_FALSE˳��ת������BCD��ĸ�4BIT��Ӧʮ���Ƶ�ʮλ;
 �������  : ��
 �� �� ֵ  : ʮ��������ת���õ���BCD��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��15��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_STD_ConvertDeciDigitToBcd(
    VOS_UINT8                           ucDeciDigit,
    VOS_BOOL                            bReverseOrder
)
{
    VOS_UINT8 ucBcd;

    if (VOS_TRUE == bReverseOrder)
    {
        /*��4BIT�洢ʮ�������ĸ�λ*/
        ucBcd  = ucDeciDigit / 10;
        /*��4BIT�洢ʮ�������ĵ�λ*/
        ucBcd |= (ucDeciDigit % 10) << 4;
    }
    else
    {
        /*��4BIT�洢ʮ�������ĵ�λ*/
        ucBcd  = ucDeciDigit % 10;
        /*��4BIT�洢ʮ�������ĸ�λ*/
        ucBcd |= (VOS_UINT8)((ucDeciDigit / 10) << 4);
    }

    return ucBcd;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdToDeciDigit
 ��������  : ��BCD���������ת����ʮ��������
 �������  : ucBcdDigit BCD���������
             bReverseOrder MN_TRUE����ת��,��BCD��ĸ�4BIT��Ӧʮ���Ƶĸ�λ;
                           MN_FALSE˳��ת������BCD��ĸ�4BIT��Ӧʮ���Ƶ�ʮλ;
 �������  : pucDigit      ת����õ���ʮ��������
 �� �� ֵ  : BCD��ת���õ���ʮ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��15��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_STD_ConvertBcdToDeciDigit(
    VOS_UINT8                           ucBcdDigit,
    VOS_BOOL                            bReverseOrder,
    VOS_UINT8                          *pucDigit
)
{
    VOS_UINT8                           ucHigher;
    VOS_UINT8                           ucLower;
    VOS_UINT32                          ulRet;

    ucHigher = (ucBcdDigit >> 4) & 0x0f;
    ucLower  = ucBcdDigit & 0x0f;
    if ((ucHigher > 9) || (ucLower > 9))
    {
        ulRet = MN_ERR_INVALIDPARM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    if (VOS_TRUE == bReverseOrder)
    {
        *pucDigit  = (VOS_UINT8)((VOS_UINT8)(ucLower * 10) + ucHigher);
    }
    else
    {
        *pucDigit  = (VOS_UINT8)((VOS_UINT8)ucHigher * 10) + ucLower;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiToDefAlpha
 ��������  : ͬ������,��ASCII���ֵת��Ϊ23038Э��涨��Default Alphabet
 �������  : pucAsciiChar          - ָ��ASCII���ָ��
             ulLen                 - ASCII�ַ��ĳ���
 �������  : pucDefAlpha           - ָ��Default Alphabet��ָ��
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��8��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertAsciiToDefAlpha(
    const VOS_UINT8                    *pucAsciiChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucDefAlpha
)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT32                          ulLoop2;
    VOS_BOOL                            bMatched;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucAsciiChar)
     || (VOS_NULL_PTR == pucDefAlpha))
    {
        return MN_ERR_NULLPTR;
    }

    ulRet = MN_ERR_NO_ERROR;
    /*
    Ŀǰ�ο�����ƽ̨��֧��23038 6.2.1 GSM 7 bit Default Alphabet���д��ڵ��ַ�����
    ��֧����չ���е��ַ���
    ASCII����GSM 7 bit Default Alphabet�������ֵı�׼ASCII�����ת��ΪGSM 7 bit Default Alphabet��
    �����ܹ�������ַ��Ѳ���ͨ��������δ���ԣ�
    ASCII���������ַ�����{�����¼Ϊ00���ض�������@��������ʧ�ܣ�
    �����ܹ�������ַ��Ѳ���ͨ��������δ���ԣ�
    ��Ҫ�ο�����ƽ̨�Ĵ�����
    */
    for (ulLoop2 = 0; ulLoop2 < ulLen; ulLoop2++)
    {
        bMatched = VOS_FALSE;
        /*7BIT convert into ASCII ,consider later!!!!!*/
        for (ucLoop1 = 0 ; ucLoop1 < TAF_STD_MAX_GSM7BITDEFALPHA_NUM ; ucLoop1++)
        {
            if (f_aucMsgAsciiSfxDefAlpha[ucLoop1] == (*pucAsciiChar))
            {
                *pucDefAlpha = ucLoop1;
                pucDefAlpha++;
                bMatched = VOS_TRUE;
                break;
            }
        }

        if (VOS_TRUE != bMatched)
        {
            ulRet = MN_ERR_INVALIDPARM;
        }

        pucAsciiChar++;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertDefAlphaToAscii
 ��������  : ͬ������,��23038Э��涨��Default Alphabetת��ΪASCII���ֵ
 �������  : pucDefAlpha    - ָ��Default Alphabet��ָ��
             ulDefAlphaLen  - Default Alphabet�ĳ���
 �������  : pucAsciiChar   - ָ��ASCII���ָ��
 			 pulAsciiCharLen- ָ��ASCII���ַ�������
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��8��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2009-09-08
    ��    ��   : F62575
    �޸�����   : ���ⵥ��:����TE��MT���ַ�������ΪIRA�����ű�������Ϊ7BIT���룬���������ַ�@�ȶ������ݣ�д�뵽SIM���е����ݴ���
  3.��    ��   : 2009-09-24
    ��    ��   : F62575
    �޸�����   : ���ⵥ��AT2D14728:�ı���ʽ�б����ȡ�����쳣
  4.��    ��   : 2010��04��10��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��AT2D18035
                 дPDU���ŵ�SIM��,BALONG��TP-SCTS�ļ�����˲�һ�£�
  5.��    ��   : 2013��08��22��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��DTS2013081408291,�޷���ʾ���ַ�û����ʾΪ�ո�
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertDefAlphaToAscii(
    const VOS_UINT8                     *pucDefAlpha,
    VOS_UINT32                          ulDefAlphaLen,
    VOS_UINT8                           *pucAsciiChar,
    VOS_UINT32                          *pulAsciiCharLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucPos;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulValidLen = 0;

    if ((VOS_NULL_PTR == pucDefAlpha)
     || (VOS_NULL_PTR == pucAsciiChar))
    {
        return MN_ERR_NULLPTR;
    }

    /*
    Ŀǰ�ο�����ƽ̨��֧��23038 6.2.1 GSM 7 bit Default Alphabet���д��ڵ��ַ�����
    ��֧����չ���е��ַ���
    ��ASCII���������ֵ�GSM 7 bit Default Alphabet����ת��Ϊ��׼ASCII�빩��ʾ�ã�
    ��չ�ַ����ת��Ϊ0XFE����ͬ�豸�϶�����˽�н��ͣ�
    �����Ǳ�׼�ַ�ת��Ϊ0XFF����ͬ�豸�϶�����˽�н��ͣ�
    ��Ҫ�ο�����ƽ̨�Ĵ�����
    */
    ulRet = MN_ERR_NO_ERROR;
    for (ulLoop = 0; ulLoop < ulDefAlphaLen; ulLoop++)
    {
        ucPos           = TAF_STD_7BIT_MASK & pucDefAlpha[ulLoop];
        *pucAsciiChar   = f_aucMsgAsciiSfxDefAlpha[ucPos];
        if (TAF_STD_NOSTANDARD_ASCII_CODE == (*pucAsciiChar))
        {
            /* modified by l65478 for DTS2013081408291 2013-08-22 begin */
            /* �Աȱ��,���޷���ʾ���ַ�ʹ�ÿո��滻 */
            (*pucAsciiChar) = ' ';
            pucAsciiChar++;
            ulValidLen++;
            /* modified by l65478 for DTS2013081408291 2013-08-22 end */
        }
        else if (TAF_STD_GSM_7BIT_EXTENSION_FLAG == (*pucAsciiChar) )
        {
            (*pucAsciiChar) = ' ';
            pucAsciiChar++;
            ulValidLen++;
        }
        else
        {
            pucAsciiChar++;
            ulValidLen++;
        }
    }

    if (ulValidLen < ulDefAlphaLen)
    {
        *pucAsciiChar = 0;
    }
    *pulAsciiCharLen = ulValidLen;

    return ulRet;
}

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

/* Added by y00218312 for CDMA 1X Iteration 2, 2014-9-30, begin */
/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdCodeToDtmf
 ��������  : ��BCD��ת����3GPP2Э���е�DTMF��ʽ����
 �������  : VOS_UINT8                           ucBcdCode
             VOS_UINT8                          *pucDtmfCode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��30��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdCodeToDtmf(
    VOS_UINT8                           ucBcdCode,
    VOS_UINT8                          *pucDtmfCode
)
{
    VOS_UINT8                            ucDtmfCode;

    if (VOS_NULL_PTR == pucDtmfCode)
    {
        return MN_ERR_NULLPTR;
    }

    /*����'0' BCD:0x00, DTMF:0x0A*/
    /*�ַ�'*' BCD:0x0A, DTMF:0x0B*/
    /*�ַ�'#' BCD:0x0B, DTMF:0x0C*/

    if (ucBcdCode == 0x00)
    {
        ucDtmfCode = 0x0A;
    }
    else if (ucBcdCode <= 0x09)
    {
        ucDtmfCode = ucBcdCode;
    }
    else if (0x0A == ucBcdCode)         /*�ַ�'*'*/
    {
        ucDtmfCode = ucBcdCode + 1;
    }
    else if (0x0B == ucBcdCode)
    {
        ucDtmfCode = ucBcdCode + 1;     /*�ַ�'#'*/
    }
    else
    {
        return MN_ERR_INVALID_BCD;
    }

    *pucDtmfCode = ucDtmfCode;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdNumberToDtmf
 ��������  : ��BCD��ʽ�ı����ַ���ת��Ϊ3GPP2Э�鶨���DTMF��ʽ���ַ���
 �������  : const VOS_UINT8                    *pucBcdNumber
             VOS_UINT8                           ucBcdLen
             VOS_UINT8                          *pucDtmfNumber
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��30��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdNumberToDtmf(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_UINT8                          *pucDtmfNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pucDtmfNumber))
    {
        return MN_ERR_NULLPTR;
    }

    /*���������ַ�����ȥ����Ч��0XFF����*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*�ж�pucBcdAddress��ָ����ַ��������һ���ֽڵĸ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*��������*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*�жϵ�ǰ�����������λ���뻹��ż��λ���룬��0��ʼ����ż��*/
        if (1 == (ucLoop % 2))
        {
            /*���������λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*�����ż��λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*������������ת����DTMF����ʽ*/
        ulRet = TAF_STD_ConvertBcdCodeToDtmf(ucBcdCode, pucDtmfNumber);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        pucDtmfNumber++;
    }

    return MN_ERR_NO_ERROR;
}

/* Added by y00218312 for CDMA 1X Iteration 2, 2014-9-30, end */

/*lint -restore */

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

