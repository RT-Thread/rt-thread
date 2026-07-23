/******************************************************************************
*Copyright(C)2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/** \file crc.c
 **
 ** Common API of crc.
 ** @link crcGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "aes.h"
/**
 *******************************************************************************
 ** \addtogroup CrcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * \brief   
 *          ADC初始化
 *
 * \param   [in]   pu32Data    待加密数据
 * \param   [in]   pu32Key     加密KEY
 * \param   [out]  pu32Cipher  加密后数据
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t AES_Encrypt(uint32_t* pu32Data, uint32_t *pu32Key, uint32_t *pu32Cipher)
{
    if ((NULL == pu32Data)||(NULL == pu32Key)||(NULL == pu32Cipher))
    {
        return ErrorInvalidParameter;
    }
    
    //Key config
    M0P_AES->KEY0 = pu32Key[0];
    M0P_AES->KEY1 = pu32Key[1];
    M0P_AES->KEY2 = pu32Key[2];
    M0P_AES->KEY3 = pu32Key[3];
		
    //Data config
    M0P_AES->DATA0 = pu32Data[0];
    M0P_AES->DATA1 = pu32Data[1];
    M0P_AES->DATA2 = pu32Data[2];
    M0P_AES->DATA3 = pu32Data[3];
				
    M0P_AES->CR_f.MODE = 0;//Encry
    M0P_AES->CR_f.START = 1;
    while(M0P_AES->CR_f.START == 1)
    {
        ;
    }
    pu32Cipher[0] = M0P_AES->DATA0;
    pu32Cipher[1] = M0P_AES->DATA1;
    pu32Cipher[2] = M0P_AES->DATA2;
    pu32Cipher[3] = M0P_AES->DATA3;	
    return Ok;
}


/**
 * \brief   
 *          ADC初始化
 *
 * \param   [in]   pu32Cipher  待解密数据
 * \param   [in]   pu32Key     加密KEY
 * \param   [out]  pu32Data    解密后数据
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t AES_Decrypt(uint32_t *pu32Cipher,uint32_t *pu32Key, uint32_t* pu32Plaintext)
{
    if ((NULL == pu32Plaintext)||(NULL == pu32Key)||(NULL == pu32Cipher))
    {
        return ErrorInvalidParameter;
    }
    
    //Key config
    M0P_AES->KEY0 = pu32Key[0];
    M0P_AES->KEY1 = pu32Key[1];
    M0P_AES->KEY2 = pu32Key[2];
    M0P_AES->KEY3 = pu32Key[3];
		
    //Data config
    M0P_AES->DATA0 = pu32Cipher[0];
    M0P_AES->DATA1 = pu32Cipher[1];
    M0P_AES->DATA2 = pu32Cipher[2];
    M0P_AES->DATA3 = pu32Cipher[3];
				
    M0P_AES->CR_f.MODE = 1;//UnEncry
    M0P_AES->CR_f.START = 1;
    while(M0P_AES->CR_f.START == 1)
    {
        ;
    }
    pu32Plaintext[0] = M0P_AES->DATA0;
    pu32Plaintext[1] = M0P_AES->DATA1;
    pu32Plaintext[2] = M0P_AES->DATA2;
    pu32Plaintext[3] = M0P_AES->DATA3;	
    return Ok;
}
//@} // CrcGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
