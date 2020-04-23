
# 数据库完整性概念和分类

## 按约束对象分类

* 域完整性约束条件

* 关系（表）完整性约束条件

## 约束来源分类

* 结构约束：函数依赖约束、主键约束、外键约束
* 内容约束：用户自定义完整性

## 约束状态分类

* 静态约束
* 动态约束

# SQL列约束和表约束——静态约束

## CREATE TABLE

{NOT NULL |                       // 非空
    [CONSTRAINT constraintname]  // 约束名
    | PRIMARY KEY               // 主键
    | CHECK(search_cond)
    | REFERENCES tablename [colname]    // 外键
        [ON DELETE {CASCADE| SET NULL}]

eg: CREATE TABLE Student (
    S# char(8) not null unique, Sname char(10),
    Ssex char(2) constraint ctssex check (Ssex='男' or Ssex = '女'),
    Sage integer check (Sage >= 1 and Sage < 150),
    D# char(2) references Dept(D#) on delete cascade,
    Sclass char(6));

## 断言 CREATE ASSERTION

# SQL触发器——动态约束

Trigger 是一种过程完整性约束，在特定时刻自动触发执行

CREATE TRIGGER trigger_name BEFORE | AFTER

{INSERT | DELETE | UPDATE [OF col]}

ON tablename []

[FOR EACH ROW | FOR EACH STATEMENT]

[WHEN {search_condition}]

{statement | BEGIN ATOMIC}


* 当一个事件发生前或后


eg:

create trigger teacher_chgsal before update of salary

on teacher

referencing new x, old  y
for each row when(x.salary < y.salary)
begin
raise_applicaion_error();
end;

# 数据库安全性概念和分类

## DBMS 安全机制

* 自主安全性机制：通过权限在用户之间传递
* 强制安全性机制：对数据和用户强制分类，使得不同类别用户访问不同类别数据
* 推断控制机制
* 数据加密存储机制

# SQL安全性

## 自主安全机制

自主安全性是通过授权机制实现的

### 实现方式

* 存储矩阵
* 视图

### SQL 授权过程

超级用户 账号级别 关系级别

* 级别一：Select
* 级别二：INSERT UPDATE DELETE
* 级别三：CREATE ALTER DROP


GRANT {privilege}

ON TABLE talbename | viewname

TO [public|use-id]

eg:

GRANT ALL Priviledges ON Employee TO Emp2001;
GRANT SELECT ON Empv2 TO emp5001;

REVOKE {PRIVILEGE} ON TABLE FROM

# 强制安全性机制



# 小结

* 数据库完整性：实体、参照、用户自定义
* SQL 完整性：列、域完整性（create table)、动态完整性（create trigger)
