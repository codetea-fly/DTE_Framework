#pragma once
#define DTEFramework_EXPORTS
#ifdef DTEFramework_EXPORTS
#define DTEFramework_API _declspec(dllexport)
#else
#define DTEFramework_API _declspec(dllimport)
#endif // DTEFramework_EXPORTS

enum errorcode {
    ERR_OK = 0,         ///< �ɹ�
    ERR_FAIL,           ///< һ���Դ���
    ERR_INNER,          ///< �ڲ�����һ����ͬһ��ģ����ʹ�ã������⹫��
    ERR_POINTER,        ///< �Ƿ�ָ��
    ERR_INVALARG,       ///< �Ƿ�����
    ERR_NOTIMPL = 5,    ///< ����δʵ��
    ERR_OUTOFMEM,       ///< �ڴ�����ʧ��/�ڴ治��
    ERR_BUFERROR,       ///< ���������󣨲��㣬���ң�
    ERR_PERM,           ///< Ȩ�޲��㣬����δ��Ȩ�Ķ���
    ERR_TIMEOUT,        ///< ��ʱ
    ERR_NOTINIT = 10,        ///< δ��ʼ��
    ERR_INITFAIL,       ///< ��ʼ��ʧ��
    ERR_ALREADY,        ///< �ѳ�ʼ�����Ѿ�������
    ERR_INPROGRESS,     ///< �������С�����״̬
    ERR_EXIST,          ///< ������Դ����(���ļ���Ŀ¼)�Ѵ���
    ERR_NOTEXIST,       ///< ��Դ����(���ļ���Ŀ¼)������豸�Ȳ�����
    ERR_BUSY,           ///< �豸����Դæ����Դ�����ã�
    ERR_FULL,           ///< �豸/��Դ����
    ERR_EMPTY,          ///< ����/�ڴ�/����Ϊ��
    ERR_OPENFAIL,       ///< ��Դ����(���ļ���Ŀ¼��socket)��ʧ��
    ERR_READFAIL,       ///< ��Դ����(���ļ���Ŀ¼��socket)��ȡ������ʧ��
    ERR_WRITEFAIL,      ///< ��Դ����(���ļ���Ŀ¼��socket)д�롢����ʧ��
    ERR_DELFAIL,        ///< ��Դ����(���ļ���Ŀ¼��socket)ɾ�����ر�ʧ��
    ERR_CODECFAIL,      ///< �ӽ��ܡ��������ʧ��
    ERR_CRC_FAIL,       ///< crcУ�����
    ERR_TOOMANY,        ///< ��Ϣ��������������̫��
    ERR_TOOSMALL,       ///< ��Ϣ��������������̫��
    ERR_NETNOTREACH,    ///< ���粻�ɴ��·�ɣ����ش���
    ERR_NETDOWN,        ///< ���粻���ã�������

    // more...

    ERR_END,            ///< ռλ����ʵ������
};
