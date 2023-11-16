/* 
 * 文件路径：src/gausskernel/optimizer/commands/define.cpp
 * 用途：将输出的 def(DefElem) 提取出相应的数据类型
 */

typedef struct DefElem {
    NodeTag type;
    char *defnamespace; /* NULL if unqualified name */
    char *defname;
    Node *arg;               /* a (Value *) or a (TypeName *) */
    DefElemAction defaction; /* unspecified action, or SET/ADD/DROP */
    int	begin_location;       /* token begin location, or -1 if unknown */
    int	end_location;       /* token end location, or -1 if unknown */
    int location;
} DefElem;

/*
 * 入参：def，当前节点的元素
 * 出参：char*
 * 作用：提取当前 def 的 char*值
 */
char* defGetString(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参：double
 * 作用：提取当前 def 的 numeric 值
 */
double defGetNumeric(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参：bool
 * 作用：提取当前 def 的 bool 值
 */
bool defGetBoolean(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参：int*
 * 作用：提取当前 def 的 0/1 值,0、false、off 返回0，空和其他返回1
 */
int defGetMixdInt(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参：int64
 * 作用：提取当前 def 的 int64 值
 */
int64 defGetInt64(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参： List
 * 作用：提取当前 def 的 name 值, 用list 返回
 */
List* defGetQualifiedName(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参：Typename
 * 作用：提取当前 def 的 Typename 值
 */
TypeName* defGetTypeName(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参：int
 * 作用：提取当前 def 的 Type 长度
 */
int defGetTypeLength(DefElem* def);

/*
 * 入参：def，当前节点的元素
 * 出参：int
 * 作用：提取当前 def 的 string 链表长度
 */
int defGetStringList(DefElem* def);

/*
 * 入参：bool
 * 出参：DefElem
 * 作用：根据当前 bool 值创建一个 DefElem 结构体
 */
DefElem* defWithOids(bool value);

/*
 * 入参：List* 输入链表
 *      name 链表中需要处理的节点名
 *      value 需要设置的值
 * 出参：List
 * 作用：将当前链表中元素名为 name 的节点值设置为value
 */
List* defSetOption(List* options, const char* name, Node* value);