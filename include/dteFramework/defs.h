#pragma once
#define DTEFramework_EXPORTS
#ifdef DTEFramework_EXPORTS
#define DTEFramework_API _declspec(dllexport)
#else
#define DTEFramework_API _declspec(dllimport)
#endif // DTEFramework_EXPORTS

enum errorcode {
    ERR_OK = 0,         ///< 成功
    ERR_FAIL,           ///< 一般性错误
    ERR_INNER,          ///< 内部错误（一般在同一个模块内使用，不对外公开
    ERR_POINTER,        ///< 非法指针
    ERR_INVALARG,       ///< 非法参数
    ERR_NOTIMPL = 5,    ///< 功能未实现
    ERR_OUTOFMEM,       ///< 内存申请失败/内存不足
    ERR_BUFERROR,       ///< 缓冲区错误（不足，错乱）
    ERR_PERM,           ///< 权限不足，访问未授权的对象
    ERR_TIMEOUT,        ///< 超时
    ERR_NOTINIT = 10,        ///< 未初始化
    ERR_INITFAIL,       ///< 初始化失败
    ERR_ALREADY,        ///< 已初始化，已经在运行
    ERR_INPROGRESS,     ///< 已在运行、进行状态
    ERR_EXIST,          ///< 申请资源对象(如文件或目录)已存在
    ERR_NOTEXIST,       ///< 资源对象(如文件或目录)、命令、设备等不存在
    ERR_BUSY,           ///< 设备或资源忙（资源不可用）
    ERR_FULL,           ///< 设备/资源已满
    ERR_EMPTY,          ///< 对象/内存/内容为空
    ERR_OPENFAIL,       ///< 资源对象(如文件或目录、socket)打开失败
    ERR_READFAIL,       ///< 资源对象(如文件或目录、socket)读取、接收失败
    ERR_WRITEFAIL,      ///< 资源对象(如文件或目录、socket)写入、发送失败
    ERR_DELFAIL,        ///< 资源对象(如文件或目录、socket)删除、关闭失败
    ERR_CODECFAIL,      ///< 加解密、编码解密失败
    ERR_CRC_FAIL,       ///< crc校验错误
    ERR_TOOMANY,        ///< 消息、缓冲区、内容太多
    ERR_TOOSMALL,       ///< 消息、缓冲区、内容太少
    ERR_NETNOTREACH,    ///< 网络不可达（无路由，网关错误）
    ERR_NETDOWN,        ///< 网络不可用（断网）

    // more...

    ERR_END,            ///< 占位，无实际作用
};
