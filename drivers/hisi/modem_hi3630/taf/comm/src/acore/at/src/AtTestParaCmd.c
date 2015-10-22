/******************************************************************************

                  ��Ȩ���� (C), 1998-2009, ��Ϊ�������޹�˾

*******************************************************************************
  �� �� ��   : atParseCore.c
  �� �� ��   : V1.0
  ��    ��   : �޾�ǿ/00064416
  ��������   : 2011-10-24
  ��������   : AT�����ʽ����

  �����б�   : TODO: ...
  �޸���ʷ   :
  1.��    �� : 2011-10-24
    ��    �� : �޾�ǿ/00064416
    �޸����� : �����ļ�

******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "AtCheckFunc.h"
#include "ATCmdProc.h"
#include "AtDataProc.h"
#include "Taf_Tafm_Remote.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/

#include "AtTestParaCmd.h"
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_TESTPARACMD_C
/*lint +e767 +e960*/


/*****************************************************************************
 �� �� ��  : At_TestCgdcont
 ��������  : cgdcont���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2011��12��19��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ
  3.��    ��   : 2012��04��10��
    ��    ��   : s62952
    �޸�����   : ���ⵥ��:DTS2012040902843
  3.��    ��   : 2012��05��03��
    ��    ��   : w00199382
    �޸�����   : ���ⵥ��:DTS2012042602550
  4.��    ��   : 2012��5��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012052404203: +CGDCONT�������Ӷ�<CID 0>��֧��
  5.��    ��   : 2012��8��10��
    ��    ��   : z60575
    �޸�����   : DTS2012081006711: ���Ӷ�IPV6�������ж�
  6.��    ��   : 2013��05��25��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
  7.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ��������
*****************************************************************************/
VOS_UINT32 At_TestCgdcont(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    /* Modified by A00165503 for DTS2012052404203, 2012-05-26, Begin */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0-31),\"IP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    /* Modified by A00165503 for DTS2012052404203, 2012-05-26, End */


#if (FEATURE_ON == FEATURE_IPV6)
    /* Modified by z60575 for DTS2012081006711, 2012-08-10, Begin */
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        /* Modified by A00165503 for DTS2012052404203, 2012-05-26, Begin */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (0-31),\"IPV6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (0-31),\"IPV4V6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        /* Modified by A00165503 for DTS2012052404203, 2012-05-26, End */
    }
    /* Modified by z60575 for DTS2012081006711, 2012-08-10, end */
#endif

    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-25, Begin */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-31),\"PPP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-25, End */

#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11),\"IP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* Added by A00165503 for DTS2011063004440, 2011-07-01, begin */
#if (FEATURE_ON == FEATURE_IPV6)
    /* Modified by z60575 for DTS2012081006711, 2012-08-10, Begin */
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (1-11),\"IPV6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (1-11),\"IPV4V6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    /* Modified by z60575 for DTS2012081006711, 2012-08-10, end */
#endif

    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-25, Begin */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (1-11),\"PPP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    /* Added by f00179208 for V3R3 PPP RPOJECT 2013-05-25, End */


#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCgdscont
 ��������  : cgdscont���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2011��12��19��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ
  3.��    ��   : 2012��3��5��
    ��    ��   : c00173809
    �޸�����   : DTS2012010604900,Cgdscont��������GU��Lģʽ��Ҫ����CID�����ȡֵ��Χ
  4.��    ��   : 2011��5��2��
    ��    ��   : w00199382
    �޸�����   : DTS2012042803139ȥ���ַ�������ය��
  5.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ,�޸���PDP������Χ
*****************************************************************************/
VOS_UINT32 At_TestCgdscont(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: (1-31),(0-31),(0-2),(0-3)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: (1-11),(0-11),(0-2),(0-3)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_TestCgtft
 ��������  : cgtft���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ
  1.��    ��   : 2012��3��24��
    ��    ��   : c00173809
    �޸�����   : DTS2012031901946,�ڲ���������ɾ��PPPЭ��
  2.��    ��   : 2012��8��10��
    ��    ��   : z60575
    �޸�����   : DTS2012081006711: ���Ӷ�IPV6�������ж�
*****************************************************************************/
VOS_UINT32 At_TestCgtft(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: \"IP\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* Modified by z60575 for DTS2012081006711, 2012-08-10, Begin */
#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: \"IPV6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: \"IPV4V6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
#endif
    /* Modified by z60575 for DTS2012081006711, 2012-08-10, end */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCgact
 ��������  : cgact���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgact(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCgcmod
 ��������  : cgcmod���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2011��12��19��
    ��    ��   : �����/00130025
    �޸�����   : ���ⵥDTS2011120604361��CGEQNEG��������ش���,CGCMOD���ش���
*****************************************************************************/
VOS_UINT32 At_TestCgcmod(VOS_UINT8 ucIndex)
{

    /* Modified  by l00130025 for DTS2011120604361, 2011-12-19, begin */

    /* CGEQNEG�Ĳ��������CGCMODE�ķ���ֵ��ͬ��ʹ����ͬ�ĺ��� */
   return At_TestCgeqnegPara(ucIndex);

    /* Modified  by l00130025 for DTS2011120604361, 2011-12-19, begin */

}

/*****************************************************************************
 �� �� ��  : At_TestCgpaddr
 ��������  : CGPADDR���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : c00173809
    �޸�����   : DTS2012010604900
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ��ɾ����״̬�ж�
*****************************************************************************/
VOS_UINT32 At_TestCgpaddr(VOS_UINT8 ucIndex)
{

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetPdpContextInfo(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGPADDR_TEST;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : At_TestCgautoPara
 ��������  : +CGAUTO���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��09��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 At_TestCgautoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestAuhtdata
 ��������  : Auhtdata���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ

  2.��    ��   : 2012��3��5��
    ��    ��   : c00173809
    �޸�����   : DTS2012010604900,authdata��������GU��Lģʽ��Ҫ����CID�����ȡֵ��Χ

  3.��    ��   : 2013��12��25��
    ��    ��   : A00165503
    �޸�����   : DTS2013122403650: ^AUTHDATA����֧��CID0
*****************************************************************************/
VOS_UINT32 At_TestAuhtdata(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    /* Modified by c00173809 for DTS2012010604900,2012-3-5,Begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* Modified by A00165503 for DTS2013122403650, 2013-12-25, Begin */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: (0-31),(0-2),,",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    /* Modified by A00165503 for DTS2013122403650, 2013-12-25, End */
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11),(0-2),,",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif
    /* Modified by c00173809 for DTS2012010604900,2012-3-5,End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestNdisconn
 ��������  : Ndisconn���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2012��5��7��
    ��    ��   : l60609
    �޸�����   : DTS2012050501603:CID��Χ����
*****************************************************************************/
VOS_UINT32 At_TestNdisconn(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    /* Modified by l60609 for DTS2012050501603,2012-5-7,Begin */
#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-20),(0,1),,,,(0,1,2,3)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-16),(0,1),,,,(0,1,2,3)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif
    /* Modified by l60609 for DTS2012050501603,2012-5-7,End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestNdisDup
 ��������  : NdisDup���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00184452
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2012��5��7��
    ��    ��   : l60609
    �޸�����   : DTS2012050501603:CID��Χ����
*****************************************************************************/
VOS_UINT32 At_TestNdisDup(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    /* Modified by l60609 for DTS2012050501603,2012-5-7,Begin */
#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-20),(0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-16),(0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif
    /* Modified by l60609 for DTS2012050501603,2012-5-7,End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_TestCgeqos
 ��������  : cgeqos���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : c00184452
    �޸�����   : PS�ں���Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgeqos(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31),(0-9),(0-262144),(0-262144),(0-262144),(0-262144)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_TestCgeqosrdp
 ��������  : cgeqosrdp���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : c00184452
    �޸�����   : PS�ں���Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgeqosrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_TestCgcontrdp
 ��������  : cgcontrdp���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : c00184452
    �޸�����   : PS�ں���Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgcontrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_TestCgscontrdp
 ��������  : cgscontrdp���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : c00184452
    �޸�����   : PS�ں���Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgscontrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_TestCgtftrdp
 ��������  : cgtftrdp���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : c00184452
    �޸�����   : PS�ں���Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgtftrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں�*/
/* DTS2012031605081 c64416 start in 2012-03-16 for ^TCHRENABLE=? */
/*****************************************************************************
 �� �� ��  : AT_TestChrgEnablePara
 ��������  : ^TCHRENABLE=? ��ѯ�Ƿ���Ҫ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��16��
    ��    ��   : �޾�ǿ
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestChrgEnablePara(VOS_UINT8 ucIndex)
{
    /* DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں� */
    VOS_INT32                           lChargeEnable = 0;

    lChargeEnable = mdrv_misc_get_charge_state(); /* BSP_TBAT_CHRStGet()) */
    /* ֻ��TRUE/FLASE�ķ���ֵ����Ч�� */
    if((lChargeEnable == TRUE)||( lChargeEnable == FALSE))
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  "%s:%d",
                                                  "^TCHRENABLE",
                                                  lChargeEnable);
        return AT_OK;
    }
    /* DTS2012041102190 : h00135900 end in 2011-04-11 AT�����ں� */
    else
    {
        return AT_ERROR;
    }
}
/* DTS2012031605081 c64416 start in 2012-03-16 for ^TCHRENABLE=? */
/* DTS2012041102190 : h00135900 start in 2011-04-11 AT�����ں� */

/* Added by y00213812 for A-GPS Project, 2012/06/27, begin */
/*****************************************************************************
 �� �� ��  : AT_TestCposrPara
 ��������  : +CPOSR�������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : A-GPS��Ŀ��������
  2.��    ��   : 2012��8��13��
    ��    ��   : l60609
    �޸�����   : MUX:����MUXͨ���Ĵ���

*****************************************************************************/
VOS_UINT32 AT_TestCposrPara(VOS_UINT8 ucIndex)
{
    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* ��ӡ���+CPOSR֧�ֵĲ������÷�Χ */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s: (0,1)",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/* Added by y00213812 for A-GPS Project, 2012/06/27, end */

/* Added by A00165503 for DTS2012091405101, 2012-09-12, Begin */
/*****************************************************************************
 �� �� ��  : AT_TestCmutPara
 ��������  : +CMUT=? ��������
 �������  : ucIndex --- �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestCmutPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
/* Added by A00165503 for DTS2012091405101, 2012-09-12, End */



/* ���º������Ǵ���Ŀ������, ֻ�Ǵ�AtExtendCmd.c�ļ����ƶ������ļ����� */
/* Added by l00171473 for V7R1C50_At_Abort, 2012-9-23, begin */

/*****************************************************************************
 �� �� ��  : At_TestVtsPara
 ��������  : VTS���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestVtsPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "+VTS: (0-9,A-D,*,#)");
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCuus1Para
 ��������  : CUUS1���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCuus1Para(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "+CUUS1:(0,1),(0,1),(0-6),(0-4),(0-3)");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCcwaPara
 ��������  : CCWA���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCcwaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCcfcPara
 ��������  : CCFC���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCcfcPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-5)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCusdPara
 ��������  : CUSD���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCusdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-2)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCpwdPara
 ��������  : CPWD���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ

  2.��    ��   : 2012��5��7��
    ��    ��   : A00165503
    �޸�����   : DTS2012050405948: +CPWD���������޶�
*****************************************************************************/
VOS_UINT32 At_TestCpwdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    /* Modified by A00165503 for DTS2012050405948, 2012-05-07, Begin */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"P2\",8),(\"SC\",8),(\"AO\",4),(\"OI\",4),(\"OX\",4),(\"AI\",4),(\"IR\",4),(\"AB\",4),(\"AG\",4),(\"AC\",4)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    /* Modified by A00165503 for DTS2012050405948, 2012-05-07, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestClckPara
 ��������  : CLCK���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ

  2.��    ��   : 2012��5��7��
    ��    ��   : A00165503
    �޸�����   : DTS2012050405948: +CLCK���������޶�
*****************************************************************************/
VOS_UINT32 At_TestClckPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    /* Modified by A00165503 for DTS2012050405948, 2012-05-07, Begin */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"SC\",\"AO\",\"OI\",\"OX\",\"AI\",\"IR\",\"AB\",\"AG\",\"AC\",\"FD\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    /* Modified by A00165503 for DTS2012050405948, 2012-05-07, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_TestCpbsPara
 ��������  : CPBS���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��28��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestCpbsPara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId, 1))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_TestCpbrPara
 ��������  : CPBR���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��28��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestCpbrPara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/* Added by f62575 for AT Project, 2011-10-28, begin */
/*****************************************************************************
 �� �� ��  : AT_TestCnmaPara
 ��������  : +CNMA����Ĳ�������
 �������  : VOS_UINT8 ucIndex  �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_TestCnmaPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if(AT_CMGF_MSG_FORMAT_PDU == pstSmsCtx->enCmgfMsgFormat)    /* TEXT��ʽ������� */
    {
        gstAtSendData.usBufLen = (TAF_UINT16)VOS_sprintf((TAF_CHAR*)pgucAtSndCodeAddr,
                                          "%s: (0-2)",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        gstAtSendData.usBufLen = 0;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_TestCpasPara
 ��������  : CPAS��������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��28��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestCpasPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0-5)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


    return AT_OK;
}
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
/*****************************************************************************
 �� �� ��  : AT_TestCscbPara
 ��������  : +CSCB����Ĳ�������
 �������  : VOS_UINT8 ucIndex  �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TestCscbPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,"%s:(0,1)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    return AT_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : AT_TestCpmsPara
 ��������  : +CPMS����Ĳ�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��20��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_TestCpmsPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    usLength  = 0;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (MN_MSG_ME_STORAGE_ENABLE == pstSmsCtx->enMsgMeStorageStatus)
    {
        usLength = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,
                    "%s: (\"SM\",\"ME\"),(\"SM\",\"ME\"),(\"SM\",\"ME\")",
                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        usLength = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,
                    "%s: (\"SM\"),(\"SM\"),(\"SM\")",
                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

    gstAtSendData.usBufLen = usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return AT_OK;
}

/* Added by f62575 for AT Project, 2011-10-28, end */

/*****************************************************************************
 �� �� ��  : At_TestCopsPara
 ��������  : cops���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00173809
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2011��10��24��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ:�޸��б��ѵĶ�ʱ������ʱ��
*****************************************************************************/
VOS_UINT32 At_TestCopsPara(TAF_UINT8 ucIndex)
{
    if (AT_SUCCESS == Taf_PhonePlmnList(gastAtClientTab[ucIndex].usClientId, 0,TAF_PLMN_LIST))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_TEST;

        /* �������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
/*****************************************************************************
 �� �� ��  : At_TestCpolPara
 ��������  : cpol���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    ��    ��   : c00173809
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2013��2��22��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 At_TestCpolPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ulRst;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   TAF_MSG_MMA_TEST_PREF_PLMN,
                                   (VOS_UINT8*)&(pstNetCtx->enPrefPlmnType),
                                   sizeof(VOS_UINT8),
                                   I0_WUEPS_PID_MMA);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    if( TAF_SUCCESS == ulRst )
    {
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/*****************************************************************************
 �� �� ��  : At_TestCgeqnegPara
 ��������  : +CGEQNEQ����Ĳ�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��24��
    ��    ��   : ����/00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��19��
    ��    ��   : �����/00130025
    �޸�����   : ���ⵥDTS2011120604361��CGEQNEG��������ش���
*****************************************************************************/
VOS_UINT32 At_TestCgeqnegPara(VOS_UINT8 ucIndex)
{

    /* Modified  by l00130025 for DTS2011120604361, 2011-12-19, begin */
    /*CGEQNEG�Ĳ��������CGACT�Ĳ�ѯ����Ĺ�������,��Ҫ��ȡ��ǰ��CID�ļ���
    ���,��TAF��ѯ��ǰ��CID�ļ������*/

    if ( VOS_OK != TAF_PS_GetPdpContextState(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) )
    {
        return AT_ERROR;
    }

    /*���Ͳ�ѯ��Ϣ�ɹ���,������״̬��ΪCGEQNEG*/
    if(AT_SUCCESS != At_StartTimer(AT_QRY_PARA_TIME,ucIndex))
    {
        AT_ERR_LOG("At_TestParaCmd:ERROR:Start Timer");
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQNEG_TEST;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */

    /*��������TAF�¼��ϱ��ĵط�,��ȡ��ǰ��ЩCID������,����ӡ��ǰ��ЩCID������.*/

    /* Modified  by l00130025 for DTS2011120604361, 2011-12-19, end */

}


/*****************************************************************************
 �� �� ��  : At_TestCgeqreqPara
 ��������  : +CGEQREQ����Ĳ�������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��24��
    ��    ��   : ����/00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��24��
    ��    ��   : f62575
    �޸�����   : DTS2011112307607,����AT�ںϷ�����֧��42M��������
  3.��    ��   : 2011��12��19��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ
  4.��    ��   : 2012��03��17��
    ��    ��   : w00199382
    �޸�����   : DTS2012031603201������������
*****************************************************************************/
VOS_UINT32 At_TestCgeqreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: \"IP\",%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING,
                                        gaucAtCrLf);

#if (FEATURE_ON == FEATURE_IPV6)

    /* Modified  by w00199382 for DTS2012031603201, 2012-03-17, begin */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s: \"IPV6\",%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING,
                                        gaucAtCrLf);

    /* Modified  by w00199382 for DTS2012031603201, 2012-03-17, end */

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s: \"IPV4V6\",%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_TestCgansPara
 ��������  : +CGANS���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��24��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgansPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1),(\"NULL\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/* Added by l60609 for V3R3 PPP RPOJECT 2013-06-07, Begin */
/*****************************************************************************
 �� �� ��  : At_TestCgansExtPara
 ��������  : ^CGANS����Ĳ��Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_TestCgansExtPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
/* Added by l60609 for V3R3 PPP RPOJECT 2013-06-07, End*/

/*****************************************************************************
 �� �� ��  : At_TestCgdnsPara
 ��������  : +CGDNS���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��24��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
  2.��    ��   : 2012��4��30��
    ��    ��   : z60575
    �޸�����   : DTS2012031400889,CGDNS������Ҫ���ؼ����CID
*****************************************************************************/
VOS_UINT32 At_TestCgdnsPara(VOS_UINT8 ucIndex)
{


    /* Modified  by z60575 for DTS2012031400889, 2012-4-30, begin */

    /* CGDNS�Ĳ��������CGCMODE�ķ���ֵ��ͬ��ʹ����ͬ�ĺ��� */
    return At_TestCgeqnegPara(ucIndex);

    /* Modified  by z60575 for DTS2012031400889, 2012-4-30, begin */
}


/*****************************************************************************
 �� �� ��  : At_TestCgdataPara
 ��������  : +CGDATA���Ժ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
*****************************************************************************/
VOS_UINT32 At_TestCgdataPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"NULL\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/* Added by l00171473 for V7R1C50_At_Abort, 2012-9-23, end */

/* Added by z00214637 for DSDA GUNAS C CORE, 2012-12-28, begin */
/*****************************************************************************
 �� �� ��  : AT_TestCbgPara
 ��������  : �������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    ��    ��   : z00214637
    �޸�����   : AT^CBG �������������
*****************************************************************************/
VOS_UINT32 AT_TestCbgPara( VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/* Added by z00214637 for DSDA GUNAS C CORE, 2012-12-28, end */

/* Added by s00217060 for V9R1_SVLTE, 2013-6-4, begin */
/*****************************************************************************
 �� �� ��  : AT_TestNCellMonitorPara
 ��������  : ^NCELLMONITOR�������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : s00217060
    �޸�����   : V9R1_SVLTE: ��������
*****************************************************************************/
VOS_UINT32 AT_TestNCellMonitorPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/* Added by s00217060 for V9R1_SVLTE, 2013-6-4, end */

/* Added by l00198894 for V9R1 AGPS, 2013/07/22, begin */
/*****************************************************************************
 �� �� ��  : AT_TestRefclkfreqPara
 ��������  : AT^REFCLKFREQ�������������
 �������  : ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
*****************************************************************************/
VOS_UINT32 AT_TestRefclkfreqPara(VOS_UINT8 ucIndex)
{
    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ��ӡ���^REFCLKFREQ֧�ֵĲ������÷�Χ */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s: (0,1)",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/* Added by l00198894 for V9R1 AGPS, 2013/07/22, end */

/* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : AT_TestCiregPara
 ��������  : +CIREG=?�������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_TestCiregPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0-2)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_TestCirepPara
 ��������  : +CIREP=?�������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 AT_TestCirepPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
#endif
/* Added by Y00213812 for VoLTE_PhaseII, 2013-09-18, end */


#ifdef  __cplusplus
#if  __cplusplus
  }
  #endif
#endif
