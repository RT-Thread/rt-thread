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

/** \file aes.c
 **
 ** Common API of AES.
 ** @link AesGroup Some description @endlink
 **
 **   - 2019-04-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32l196_aes.h"
/**
 *******************************************************************************
 ** \addtogroup AesGroup
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
 *          AES 加密
 *
 * \param   [in]   pstcAesCfg    AES 配置结构体 @ref stc_aes_cfg_t
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t AES_Encrypt(stc_aes_cfg_t* pstcAesCfg)
{
    if (NULL == pstcAesCfg)
    {
        return ErrorInvalidParameter;
    }
    
    M0P_AES->CR_f.KEYSIZE = pstcAesCfg->enKeyLen;
    
    //Key cfg
    M0P_AES->KEY0 = pstcAesCfg->pu32Key[0];
    M0P_AES->KEY1 = pstcAesCfg->pu32Key[1];
    M0P_AES->KEY2 = pstcAesCfg->pu32Key[2];
    M0P_AES->KEY3 = pstcAesCfg->pu32Key[3];        
    
    if(AesKey192 == pstcAesCfg->enKeyLen)
    {
            M0P_AES->KEY4 = pstcAesCfg->pu32Key[4];
            M0P_AES->KEY5 = pstcAesCfg->pu32Key[5];    
    }
    
    if(AesKey256 == pstcAesCfg->enKeyLen)
    {
            M0P_AES->KEY4 = pstcAesCfg->pu32Key[4];
            M0P_AES->KEY5 = pstcAesCfg->pu32Key[5];
            M0P_AES->KEY6 = pstcAesCfg->pu32Key[6];
            M0P_AES->KEY7 = pstcAesCfg->pu32Key[7];
    }
        
    //Data cfg
    M0P_AES->DATA0 = pstcAesCfg->pu32Plaintext[0];
    M0P_AES->DATA1 = pstcAesCfg->pu32Plaintext[1];
    M0P_AES->DATA2 = pstcAesCfg->pu32Plaintext[2];
    M0P_AES->DATA3 = pstcAesCfg->pu32Plaintext[3];
                
    M0P_AES->CR_f.MODE = 0;//Encry
    M0P_AES->CR_f.START = 1;
    while(M0P_AES->CR_f.START == 1)
    {
        ;
    }
    pstcAesCfg->pu32Cipher[0] = M0P_AES->DATA0;
    pstcAesCfg->pu32Cipher[1] = M0P_AES->DATA1;
    pstcAesCfg->pu32Cipher[2] = M0P_AES->DATA2;
    pstcAesCfg->pu32Cipher[3] = M0P_AES->DATA3;    
    return Ok;
}


/**
 * \brief   
 *          AES 解密
 *
 * \param   [in]   pstcAesCfg    AES 配置结构体 @ref stc_aes_cfg_t
 *
 * \retval  en_result_t  Ok:  配置成功
 * \retval  en_result_t  ErrorInvalidParameter: 无效参数
 */
en_result_t AES_Decrypt(stc_aes_cfg_t* pstcAesCfg)
{
    if (NULL == pstcAesCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_AES->CR_f.KEYSIZE = pstcAesCfg->enKeyLen;
	    
    //Key cfg
    M0P_AES->KEY0 = pstcAesCfg->pu32Key[0];
    M0P_AES->KEY1 = pstcAesCfg->pu32Key[1];
    M0P_AES->KEY2 = pstcAesCfg->pu32Key[2];
    M0P_AES->KEY3 = pstcAesCfg->pu32Key[3];

    if(AesKey192 == pstcAesCfg->enKeyLen)
    {
            M0P_AES->KEY4 = pstcAesCfg->pu32Key[4];
            M0P_AES->KEY5 = pstcAesCfg->pu32Key[5];    
    }
    
    if(AesKey256 == pstcAesCfg->enKeyLen)
    {
            M0P_AES->KEY4 = pstcAesCfg->pu32Key[4];
            M0P_AES->KEY5 = pstcAesCfg->pu32Key[5];
            M0P_AES->KEY6 = pstcAesCfg->pu32Key[6];
            M0P_AES->KEY7 = pstcAesCfg->pu32Key[7];
    }        
        
    //Data cfg
    M0P_AES->DATA0 = pstcAesCfg->pu32Cipher[0];
    M0P_AES->DATA1 = pstcAesCfg->pu32Cipher[1];
    M0P_AES->DATA2 = pstcAesCfg->pu32Cipher[2];
    M0P_AES->DATA3 = pstcAesCfg->pu32Cipher[3];
                
    M0P_AES->CR_f.MODE = 1;//UnEncry
    M0P_AES->CR_f.START = 1;
    while(M0P_AES->CR_f.START == 1)
    {
        ;
    }
    pstcAesCfg->pu32Plaintext[0] = M0P_AES->DATA0;
    pstcAesCfg->pu32Plaintext[1] = M0P_AES->DATA1;
    pstcAesCfg->pu32Plaintext[2] = M0P_AES->DATA2;
    pstcAesCfg->pu32Plaintext[3] = M0P_AES->DATA3;
    return Ok;
}

//@} // AesGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
