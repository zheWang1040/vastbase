/*
 * 文件路径: src/gausskernel/optimizer/commands/obs_stream.cpp
 * 用途: 继承于 BulkLoadStream 实现接口，用于读写 url 路径中文件
 */

class OBSStream : public BulkLoadStream {
public:
    /* 
     * 构造函数，根据入参 format 构造初始化解析器 parser
     */
    OBSStream(FileFormat format, bool is_write);
    virtual ~OBSStream();

    /* 
     * Routines inherited from interface
     * 记录传入的 url 路径，检查路径合法性；同时初始化 CSV 解析器参数
     */
    void Initialize(const char* uri, CopyState cstate);

    /* 
     * 关闭当前读写流
     */
    void Close(); /* virtual function */

    /* 
     * 从当前 stream 中读取数据，咱叔未使用
     */
    int Read(); /* virtual function */

    /* 
     * 同 Read()，暂时未使用
     */
    int InternalRead(); /* virtual function */

    /* 
     * 同 Read()，暂时未使用
     */
    int ReadMessage(StringInfoData& dst); /* virtual function */

    /* 
     * src：原始数据, len : 路径
     * 将数据写入当前文件流
     */
    int Write(void* src, Size len); /* virtual function */

    /* 
     * Flush current segment to OBS and also free m_buffile handler
     * 将当前段数据写入 OBS 并清空当前缓冲；
     */
    
    void Flush(); /* virtual function */

    // 用于检查 Initialize() 中传入的 url 是否合法
    void VerifyAddr();

    /* Getter & Setter */
    inline GDS::Parser* GetOBSParser() const;

    // 设置当前 parser 的缓冲长度
    void set_parser_chunksize(uint32_t chunksize);

    // 设置当前 obs 复制的 options
    void set_source_obs_copy_options(ObsCopyOptions* options);

    // 获取记录的 options;
    const ObsCopyOptions* get_obs_copy_options(void);

    // 记录当前 option 中秘钥
    void set_obs_copy_options(ObsCopyOptions* options);

    // 开始一个新的段 segment
    const char* StartNewSegment(void);
};

// 使用路径和任务列表初始化 OBS 模块状态
void initOBSModeState(CopyState cstate, const char* objectpath, List* totalTask);

// 结束 OBS 模块加载
void endOBSModeBulkLoad(CopyState cstate);

/*
 * Fetch a line of data into line buffer and let uper layer to do line-2-heap tuple
 * parsing
 * 获取一行数据放入缓冲区，同时让上层处理将行转换为堆表进行解析
 */
bool CopyGetNextLineFromOBS(CopyState cstate);

/*
 * Start processing next OBS object assigned to current DN, return 'FALSE' indicates
 * there is no more tasks to for this DN and 'TRUE' to start next one
 * 处理当前 DN 中下一个 OBS 对象，当存在任务时返回true, 当前 DN 已经没有任务返回false
 */
bool getNextOBS(CopyState cstate);


