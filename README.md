# 银行信息管理系统
## 1.项目介绍
 * 模拟银行信息系统实现功能
## 2.说明
* 模拟银行ATM机操作
* 显示用户管理
* 用户交易
## 3.管理员功能
  * __开户__
  > 用户注册,名字(可以重复，重名会提示)，电话号码11位(不可重复)，密码(六位数)
  * __销户__
  > 消除所有信息
  * __登陆__
  > 已注册用户登陆
  * __修改__
  > 修改信息：用户名、电话号码、密码
  * __查看__
  > 查看所有信息，查找指定用户
  * __解冻__
  > 用户输入错三次密码后，账号则会冻结，需要管理员登陆管理员端解冻
## 4. 客户端功能
   * __存钱__
   >输入钱数，存储到该用户数据库中
   * __取钱__
   >输入钱数，取出，相应的数据库该用户的数据钱也会减少
   * __转账__
   >用户输入要转账的账号，找到则输入金额，转账
   * __查看__
   >可以看到用户的基本信息
   * __修改__
   >可以修改用户密码和更改电话号码
## 4.技术
  >运用了结构体存储数据，
  >文件IO保存数据到本地，读取到数据库
  >状态机
  >指针传参
## 5.其他
  增加了日志功能
  >可以查看文件log.txt,来查看系统运行时间，开户、销户、转账记录
  >通过文件IO可以实现了程序多终端运行，数据同步
 
