#ifndef _HISILICON_EFUSE_H_
#define _HISILICON_EFUSE_H_

typedef enum tag_efuse_log_level {
    log_level_disable = 0,
    log_level_error = 1,
    log_level_warning,
    log_level_debug,
    log_level_info ,
    log_level_total = log_level_info
}EFUSE_LOG_LEVEL;

typedef enum tag_efuse_mem_attribution {
    efuse_mem_attr_none = -1,
    efuse_mem_attr_huk = 0,
    efuse_mem_attr_scp,
    efuse_mem_attr_authkey,
    efuse_mem_attr_chipid,
    efuse_mem_attr_tsensor_calibration,
    efuse_mem_attr_huk_rd_disable,
    efuse_mem_attr_authkey_rd_disable,
    efuse_mem_attr_dbg_class_ctrl,
    efuse_mem_attr_dieid,
    efuse_mem_attr_max
}EFUSE_MEM_ATTRIBUTION;

typedef struct tag_efuse_attribution_info {
    unsigned int bits_width;
}EFUSE_ATTRIBUTION_INFO;

typedef struct tag_efusec_data{
    EFUSE_ATTRIBUTION_INFO efuse_attrs_parsed_from_dts[efuse_mem_attr_max];
}EFUSEC_DATA;

#define OK                      (0)     /* �ɹ� */
#define ERROR                   (-1)    /* ������������Ͳ�֧�� ���ִ������*/
#define ERROR_EXIT_PD           (-2)    /* �����˳�power downģʽ */
#define ERROR_ENTER_PD          (-3)    /* �����˳�power downģʽ */
#define ERROR_APB_PGM_DIS       (-4)    /* ��ǰeFusec��������д */
#define ERROR_EFUSEC_READ       (-5)    /* �������һ��eFuse������ */
#define ERROR_PRE_WRITE         (-6)    /* δ���Ԥ��д��λ */
#define ERROR_PG_OPERATION      (-7)    /* �������һ��eFuseд���� */


#define HISI_EFUSE_READ_CHIPID             0x1000
#define HISI_EFUSE_READ_DIEID              0x2000
#define HISI_EFUSE_WRITE_CHIPID            0x3000
#define HISI_EFUSE_READ_AUTHKEY            0x4000
#define HISI_EFUSE_WRITE_AUTHKEY           0x5000
#define HISI_EFUSE_READ_CHIPIDLEN          0x6000
#define HISI_EFUSE_WRITE_DEBUGMODE         0x7000
#define HISI_EFUSE_READ_DEBUGMODE          0x8000

#define HISI_EFUSE_READ_THERMAL            0x9000
#define HISI_EFUSE_TEST_DISPLAY            0xa000


//#define HISI_EFUSE_DEBUG 1

#if HISI_EFUSE_DEBUG == 1
#define HISI_EFUSE_TEST_WR           0xa001
#define HISI_EFUSE_TEST_READ_CHIPID  0xa002
#define HISI_EFUSE_TEST_READ_DIEID   0xa003
#define HISI_EFUSE_TEST_READ_KCE     0xa004
#define HISI_EFUSE_TEST_WRITE_KCE    0xa005

#endif


#define EFUSE_BUF_SIZE                     (256)

extern int get_efuse_dieid_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int get_efuse_chipid_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int set_efuse_chipid_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int get_efuse_authkey_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int set_efuse_authkey_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int get_efuse_securitydebug_value(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
extern int set_efuse_securitydebug_value(unsigned char *pu8Buffer, unsigned int timeout);
extern int get_efuse_thermal_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);
extern int get_efuse_carrierid_value(unsigned char *pu8Buffer, unsigned int u32Length, unsigned int timeout);

#ifdef CONFIG_HI3XXX_EFUSE
/*****************************************************************************
* �� �� ��  : bsp_efuse_read
*
* ��������  : �����ȡEFUSE�е�����
*
* �������  : group  ��ʼgroup
*                   num  ���鳤��(word��,������16)
* �������  : pBuf ��EFUSE�е�����
*
* �� �� ֵ  : 
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_efuse_read(unsigned int * pBuf, const unsigned int group, const unsigned int num);

/*****************************************************************************
* �� �� ��  : bsp_efuse_write
*
* ��������  : ��дEfsue
*
* �������  : pBuf:����д��EFUSEֵ
*                 group,Efuse��ַƫ��
*                 len,��д����
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int bsp_efuse_write(unsigned int *pBuf, const unsigned int group, const unsigned int num);
#endif


extern int test_efuse_display(unsigned char *pu8Buffer, unsigned int u32Lenght, unsigned int timeout);
#if HISI_EFUSE_DEBUG == 1
extern int test_efuse_wr(unsigned int timeout);
#endif
#endif
