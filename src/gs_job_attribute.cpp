/*
 * 文件路径: src/common/backend/catalog/gs_job_attribute.cpp
 * 用途: 用于记录创建 job 的相关属性
 */

/*
 * 获取 job_scheduler 的最大时间戳，默认为:'4000-1-1'
 * 返回：时间戳的 datum
 */
Datum get_scheduler_max_timestamp();


/*
 * 获取 job_scheduler 的最大时间戳，将时间戳转转为 GMT，默认为:'4000-1-1'
 * 返回：时间戳的 datum
 */
Datum get_scheduler_max_timestamptz();

/*
 * 根据 role oid 获取该角色名字
 * 返回：role 对应的名字
 */
char *get_role_name_str(Oid oid);

/*
 * 获取 role id 的 text 类型
 * 返回：role 对应的名字
 */
Datum get_role_datum(Datum name);

/*
 * 根据 role text 类型获取 role id
 * 返回：role 对应的 role id
 */
char *get_raw_role_str(Datum name);


/*
 * 获取默认参数类型
 * 返回：默认参数类型的 datum
 */
Datum get_default_argument_type();


/*
 * 获取当前任务的节点名，可能为空字符串
 * 返回：任务节点名的 datum
 */
static Datum get_pg_job_node_name();

/*
 * 检查 program_name 是否以: INLINE_JOB_PROGRAM_PREFIX 起始
 * 返回：bool
 */
bool is_inlined_program(Datum program_name);


/*
 * 检查 schedule_name 是否以: INLINE_JOB_SCHEDULE_PREFIX 起始
 * 返回：bool
 */
bool is_inlined_schedule(Datum schedule_name);

/*
 * 检查 nameStr 是否为合法字符串，最大长度为 1024-17
 * 返回：bool
 */
static bool IsLegalNameStr(const char* nameStr, bool *hasAlpha);


/*
 * 检查 job_name 是否正在执行中
 * 返回：bool
 */
bool is_job_running(Datum job_name);


/*
 * 检查 job_name 是否可以被停止
 * 返回：bool
 */
static void can_disable_job(Datum job_name);

/*
 * 获取 job 对象 object 的 attribute 对应的属性值;
 * lockmode 加锁方式
 * miss_ok 是否可以丢失
 * can_be_null 属性值是否可以为空
 * 返回: datum 属性值
 */
Datum get_attribute_value(Datum object, const char *attribute, LOCKMODE lockmode, bool miss_ok, bool can_be_null);

/*
 * 获取 job 对象 object 的 attribute 对应的属性值，返回属性值的字符形式
 * lockmode 加锁方式
 * miss_ok 是否可以丢失
 * can_be_null 属性值是否可以为空
 * 返回: datum 字符形式
 */
char *get_attribute_value_str(Datum object, const char *attribute, LOCKMODE lockmode, bool miss_ok, bool can_be_null);


/*
 * 检查 object_name 是否对当前用户可见
 * is_readonly 检查当前用户是否可以执行 job 
 * 返回: void
 */
void check_object_is_visible(Datum object_name, bool is_readonly);

/*
 * 检查 object_name 和 object_type 是否匹配
 * 返回: void
 */
void check_object_type_matched(Datum object_name, const char *object_type);

/*
 * 获取 job 类型的字符输出
 * job_name: job name
 * miss_ok:  是否允许对丢失
 */
char *get_job_type(Datum job_name, bool miss_ok);

/*
 * 获取 program 的参数个数
 * program_name: program name
 * miss_ok:  是否允许对丢失
 */
int get_program_number_of_arguments(Datum program_name, bool miss_ok);

/*
 * 将属性插入 gs_job_attribute 系统表中
 * gs_job_attribute_rel: 表名
 * attribute_name: 属性名
 * attribute_value: 属性值
 * values: gs_job_attribute 系统表值
 * nulls：gs_job_attribute 系统表是否为空
 */
static void insert_gs_job_attribute(const Relation gs_job_attribute_rel, const Datum attribute_name,
                                    const Datum attribute_value, Datum *values, bool *nulls);

/*
 * 将属性插入 gs_job_attribute 系统表中
 * object_name : 对象名
 * attribute_name: 属性名
 * attribute_value: 属性值
 * 内部调用 insert_gs_job_attribute
 */
void insert_attribute(const Datum object_name, const Datum attribute_name, const Datum attribute_value);

/*
 * 将对象多个属性插入 gs_job_attribute 系统表中
 * object_name : 对象名
 * attribute_name: 属性名
 * attribute_value: 属性值
 * n:             : 属性个数
 * 内部调用 insert_gs_job_attribute
 */
void multi_insert_attribute(const Datum object_name, const Datum *attribute_name, const Datum *attribute_value, int n);

/*
 * 更新系统表中对象的属性值
 * object_name : 对象名
 * attribute_name: 属性名
 * attribute_value: 属性值
 */
void update_attribute(Datum object_name, Datum attribute_name, Datum attribute_value);

/*
 * 检查当前用户是否有操作权利
 * username : 对象名
 * authorization: 操作类型
 */
void check_privilege(char *username, const char *authorization);

/*
 * 检查当前权利是否合法
 * privilege : 特权名
 */
void check_authorization_valid(Datum privilege);

/*
 * 给用户赋予权利
 * privilege : 特权名
 */
void grant_user_authorization_internal(PG_FUNCTION_ARGS);


/*
 * 获取当前用户名
 */
static char* get_current_username();

/*
 * 检查 credential 是否合法
 * username : credential_name
 */
static void check_credential_name_valid(const Datum username);

/*
 * 创建一个 credential
 */
void create_credential_internal(PG_FUNCTION_ARGS);

/*
 * 检查 schedule name是否合法
 * schedule_name : schedule_name
 */
static void check_schedule_name_valid(Datum schedule_name)

/*
 * 检查创建 schedule 的权限
 */
static void check_schedule_creation_privilege();

/*
 * 创建 schedule 
 */
void create_schedule_internal(PG_FUNCTION_ARGS);

/*
 * 检查 program name是否合法
 * program_name : program_name
 */
static void check_program_name_valid(Datum program_name, bool is_inline);

/*
 * 检查 program type 是否合法
 * program_type : program_type
 */
static void check_program_type_valid(Datum program_type);

/*
 * 检查创建 program 的权限
 */
static void check_program_creation_privilege(Datum program_type);

/*
 * 检查创建 program 的行为
 */
void check_program_action(Datum action);

/*
 * 创建 program 
 */
void create_program_internal(PG_FUNCTION_ARGS, bool is_inline);


/*
 * job 插入 pg_job 系统表
 * name: job name
 * job_id: job id
 * start_date: job start time
 * interval: job 调度时间间隔
 * end_date: job end time
 * enabled: job enable/disable
 * priv_user: job prov user
 * log_user: job log user
 * schema_name: scheduler name which job belonged to.
 */
static void dbe_insert_pg_job(Datum name, Datum job_id, Datum start_date, Datum interval, Datum end_date, Datum enabled,
                              Datum priv_user, Datum log_user, Datum schema_name);

/*
 * 获取当前job对应的scheduler
 * job_name: job name
 * 返回 : job 对应的 scheduler name
 */
char *get_inline_schedule_name(Datum job_name);

/*
 * 创建事件任务
 * job_name: job name
 * job_type: job type
 * job_action: 执行 job 对应的动作
 * job_definer: job 的定义者
 * 返回 : job 对应的 program name
 */
char *CreateEventInlineProgram(Datum job_name, Datum job_type, Datum job_action, Datum job_definer);

/*
 * 获取当前 job 对应的 job id
 * 返回 : job 对应的 job id
 */
static int get_job_id();

/*
 * 检查当前创建 job 的权限
 * job_type : job type
 */
static void check_job_creation_privilege(Datum job_type);

/*
 * 检查当前创建 job name 的合法性
 * job_name : job name
 */
static void check_job_name_valid(Datum job_name);

/*
 * 获取当前任务的特权用户
 * program_name : program name
 * job_intype: job type
 */
Datum get_priv_user(Datum program_name, Datum job_intype);

/*
 * 底层创建 job 接口函数
 */
void create_job_raw(PG_FUNCTION_ARGS);

/*
 * 外层创建 job 接口函数，最后会调create_job_raw
 */
void create_job_1_internal(PG_FUNCTION_ARGS);
void create_job_2_internal(PG_FUNCTION_ARGS);
void create_job_3_internal(PG_FUNCTION_ARGS);
void create_job_4_internal(PG_FUNCTION_ARGS);

/*
 * 获取 scheduler 相关信息
 * schedule_name : scheduler name
 * start_date: 起始时间
 * repeat_interval: 时间间隔
 * end_date: 终止时间
 */
static void get_schedule_info(Datum schedule_name, Datum *start_date, Datum *repeat_interval, Datum *end_date);

/*
 * 获取 program 相关信息
 * program_name : program name
 * job_action: job action
 * num_of_args: 参数个数
 * enabled: 启用 job 开关
 */
void get_program_info(Datum program_name, Datum *job_type, Datum *job_action, Datum *num_of_args, Datum *enabled);

/*
 * 检查 job class 名合法性
 * job_class_name : job class name
 */
static void check_job_class_name_valid(Datum job_class_name);

/*
 * 检查创建 job class 的权限
 */
static void check_job_class_creation_privilege();

/*
 * 创建 job class 接口
 */
void create_job_class_internal(PG_FUNCTION_ARGS);

/*
 * 设置 program 的动作
 * program_name : program name
 * program_action : program action
 */
static void set_program_action(const Datum program_name, const Datum program_action);

/*
 * 设置 class 的属性
 * job_class_name : job class name
 * attribute_name : attribute name
 * attribute_value: attribute value
 */
static void set_job_class_attribute(const Datum job_class_name, const Datum attribute_name, Datum attribute_value);

/*
 * 设置 program 的属性
 * program_name : program name
 * attribute_name : attribute name
 * attribute_value: attribute value
 */
static void set_program_attribute(const Datum program_name, const Datum attribute_name, Datum attribute_value);

/*
 * 设置 attribute 的属性
 * scheduler_name : scheduler name
 * attribute_name : attribute name
 * attribute_value: attribute value
 */
static void set_schedule_attribute(const Datum schedule_name, const Datum attribute_name, Datum attribute_value);


/*
 * 获取 scheduler 的属性
 * job_name : job name
 * attribute_name : attribute name
 * attribute_value: attribute value
 * attribute_name_str: char* 类型属性名
 */
static bool set_job_inline_schedule_attribute(const Datum job_name, const Datum attribute_name,
                                              const Datum attribute_value, char *attribute_name_str);


/*
 * 获取 program 的属性
 * job_name : job name
 * attribute_name : attribute name
 * attribute_value: attribute value
 * attribute_name_str: char* 类型属性名
 */
static bool set_job_inline_program_attribute(const Datum job_name, const Datum attribute_name,
                                             const Datum attribute_value, char *attribute_name_str);


/*
 * 设置 job 关联对象的属性
 * job_name : job name
 * attribute_name : attribute name
 * attribute_value: attribute value
 * attribute_name_str: char* 类型属性名
 */
static bool set_job_associated_object_attribute(const Datum job_name, const Datum attribute_name,
                                                const Datum attribute_value, char *attribute_name_str);

/*
 * 设置 job 的属性
 * job_name : job name
 * attribute_name : attribute name
 * attribute_value: attribute value
 */
void set_job_attribute(const Datum job_name, const Datum attribute_name, const Datum attribute_value);

/*
 * 设置属性关联表
 * object_name : object name
 * attribute_name : attribute name
 * attribute_value: attribute value
 */
void set_attribute_with_related_rel(const Datum object_name, const Datum attribute_name, const Datum attribute_value);

/*
 * 设置属性
 * object_name : object name
 * type: 类型
 */
void set_attribute_1_internal(PG_FUNCTION_ARGS, Oid type);

/*
 * 准备设置属性
 * attribute : 属性
 * name: 名
 * value：值
 * extra_name：扩展名
 * extra_value：扩展值
 */
void prepare_set_attribute(Datum attribute, Datum *name, Datum *value, Datum *extra_name, Datum extra_value);

/*
 * 设置属性接口
 */
void set_attribute_2_internal(PG_FUNCTION_ARGS);

/*
 * 支持 job 开始执行
 * job_class_name: job class name
 * enable_value: enable/disable
 * force: true/false
 */
static void enable_job_by_job_class(const Datum job_class_name, Datum enable_value, bool force);

/*
 * 检查使用 program 权限
 * rel: 表名
 * program_name: program name
 */
static void check_enable_program_privilege(Relation rel, Datum program_name);

/*
 * 检查参数是否定义
 * program_name: 程序名
 * number_of_arguments: 参数个数
 */
void check_if_arguments_defined(Datum program_name, int number_of_arguments);

/*
 * 准许程序执行
 * program_name: 程序名
 * enable_value: 支持值
 */
void enable_program(Datum program_name, Datum enable_value);

/*
 * 强制准许单个对象执行
 * object_name: 对象名
 * enable_value: 支持值
 * force：是否强制
 */
void enable_single_force(Datum object_name, Datum enable_value, bool force);

/*
 * 准许单个对象执行
 */
void enable_single_internal(PG_FUNCTION_ARGS);

/*
 * 不准许单个对象执行
 */
void disable_single_internal(PG_FUNCTION_ARGS);