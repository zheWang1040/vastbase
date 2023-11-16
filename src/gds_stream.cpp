/*
 * 文件路径: src/gausskernel/optimizer/commands/gds_stream.cpp
 * 用途: 根据 url 初始化 gds 流，从数据流中读写通信
 */

/*
 * GDSUri 公有继承 BaseObject 接口;
 */
class GDSUri : public BaseObject {
public:
    GDSUri();
    ~GDSUri();
    /*
     * 入参: 字符形式的 url
     * 出参: void
     * 功能: 处理解析 url 地址，记录处理后的 url 地址
     */
    void Parse(const char* uri);

    /*
     * 入参: void
     * 出参: char*
     * 功能: 处理解析 url 地址，记录处理后的 url 地址
     */
    const char* ToString();
    /*
     * 入参: char*
     * 出参: void
     * 功能: 裁剪当前 str 为指定格式
     */
    static void Trim(char* str);
};

class GDSStream : public BulkLoadStream {
public:
    GDSStream();
    virtual ~GDSStream();

    // 根据给定的url 建立连接
    void Initialize(const char* uri);

    // 关闭 socket 连接
    void Close();

    // 读取数据流，暴露给外层的接口
    int Read();

    // 将发送数据写入 dst，返回写入长度
    int ReadMessage(StringInfoData& dst);

    // 往 socket 中写入字节流
    int Write(void* src, Size len);

    // 刷新缓冲区
    void Flush();

    // 检查输入的 url 是否为合法地址
    void VerifyAddr();

private:
    /* function type pointer defination */
    typedef int (GDSStream::*readfun)(void);
    /*
     * 准备读取 buffer, 在读数据前调用;
     * 主要用于检查：
     * 1. 向前读取数据时缓冲区是否为空;
     * 2. 必要时增大输入 buffer
     */
    void PrepareReadBuf(void);

    /*
     * 从 socket 中读取数据
     * 返回值: 1 读取成功; 0 没有读到数据，重试; -1 读取错误
     */
    int InternalRead(void);

    /*
     * 从 openSSL buffer 中读取数据
     * 返回值: 1 读取成功; 0 没有读到数据，重试; <0 读取异常
     */
    int InternalReadSSL(void);

    // 初始化 GDSStream 对象 SSL
    void InitSSL(void);
};

/*
 * 入参: cmd: 指令类型；
 *      buf: 指令内容，将数据写入该 buf 中
 * 功能: 根据指令类型，将数据写入buf 中
 */
extern void SerializeCmd(CmdBase* cmd, StringInfo buf);

/*
 * 入参:  buf: 指令内容
 * 返回值: CmdBase 指令类型
 * 功能: 根据 buf 中内容，确认指令类型
 */
extern CmdBase* DeserializeCmd(StringInfo buf);

/*
 * 入参:  dst 待发送的组装数据
 *       date 待发送的数据
 * 功能: 将data 数据添加包头，写入dest
 */
extern void PackData(StringInfo dest, StringInfo data);
