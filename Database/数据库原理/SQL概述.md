# SQL概述

学生选课数据库 SCT

* Student(S# char(8), Sname char(10), Ssex char(2), Sage integer, D# char(2), Sclass char(6))

* Dept(D# char(2), Dname char(10), Dean char(10))

* Course(C# char(3), Cname char(12), Chours integer, Credit float(1), T# char(3))

* Teacher(T# char(3), Tname char(10), D# char(2), Salary float(2))

* SC(S# char(8), C# char(3), Score float(1))




# DDL

## CREATE

创建数据库

```SQL
CREATE DATABASE SCT;
```

创建表
```SQL
CREATE TABLE 表名(列名 数据类型 Primary Key|Unique  Not null);
```

## ALTER

修正数据库的 **定义**

```sql
ALTER TABLE 表名
[ADD 列名 数据类型...]     增加新列
[DROP 完整性约束]          删除完整性约束
[MODIFY 列名 数据类型...]  修改列定义
```

## DROP

撤销基本表/DB

```sql
DROP TABLE 表名;

DROP DATABASE SCT;
```

**注意 DROP 与 DELETE 的区分**


# DML

## INSERT

省略列名，数据需与存储列名一致
```sql
INSERT INTO 表名 
VALUES (值，值...);
```

数据须与语句中列名一致
```sql
INSERT INTO 表名(列名，列名....) 
VALUES (值，值...);
```
## DELETE

```sql
DELETE FROM 表名 WHERE ();
```

## UPDATE

```SQL
UPDATE 表名
SET 列名=表达式|(子查询) , .. WHERE ();
```

eg：

```sql
UPDATE Teacher
SET Salary = Salary * 1.05;
```

## SELECT

```sql
SELECT (列名，列名) FROM 表名 WHERE (检索条件);

SELECT * FROM 表名 WHERE (检索条件);
```

### 批元组新增

```sql
INSERT INTO Table(列名，列名)
SELECT 列名，列名 FROM Table2
WHERE (检索条件);
```
### 结构唯一性问题：

Table 中要求无重复元组通过 Primary key 或 Unique 保证，无重复元组通过 DISTINCT 实现

```sql
SELECT DISTINCT S#
FROM SC
WHERE Score > 80;
```

### 结果排序问题

```sql
ORDER BY 列名 [ASC | DESC]
```

### 模糊查询

```sql
列名 [not] like "字符串"
```

% 匹配 0 个或多个字符
_ 匹配任意单个字符
\ 转义字符

### 多表联合查询

```sql
SELECT (列名,列名...) FROM 表名，表名... WEHERE 检索条件
```

表属性相同：表名.属性名 限定

表名相同：表名1 as(可省略) 别名1，表名2 as 别名2

eg: 求有薪水差额的任意两位教师

```sql
SELECT T1.Tname as t1, T2.Tname as t2
FROM Teacher tt1, Teacher tt2
WHERE t1.salary > t2.salary;
```

**必须大于或小于，不等于会重复**


# DCL

## GRANT

## REVOKE


# 小结

* DDL：CREATE DATABASE / CREATE TABLE

* DML: INSERT / UPDATE / DELETE / SELECT(单表查询、多表查询、模糊查询、结果排序、结果去重、条件书写)