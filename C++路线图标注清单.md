# C++ 学习路线 · 三档标注清单（Middle + Senior）

> 标注方法：每行把「会 / 半懂 / 不会」改成你的结论；已彻底掌握的整行删掉即可。  
> 标完「半懂/不会」的节点，就是下一步要补的缺口。

## 中级 Middle（应已达标，用于自检）

### 语法

- [ ] `bitwise-operations` 位运算 （基本运算） —— **会**
- [ ] `operators` 运算符 （函数） ——**&#x20;不会**
- [ ] `lambda` Lambda表达式 （函数） ——**&#x20;半懂**
- [ ] `static-typing` 静态类型 （数据类型） —— **会**
- [ ] `dynamic-typing` 动态类型 （数据类型） ——**不会**
- [ ] `rtti` RTTI（运行时类型识别） （数据类型 > 动态类型） —— **不会**
- [ ] `weak-ptr` weak_ptr （指针&引用 > 智能指针（smart pointer）） ——**半懂&#x20;**
- [ ] `the-rule-of-zero` 三/五/零法则 （结构体（Struct）和类（class）） —— **半懂&#x20;**
- [ ] `multiple-inheritance` 多重继承（Multiple inheritance） （结构体（Struct）和类（class）） —— **半懂&#x20;**
- [ ] `diamond-inheritance` 钻石继承（Diamond inheritance） （结构体（Struct）和类（class） > 多重继承（Multiple inheritance）） ——**半懂**
- [ ] `std-optional-std-expected` std::optional / std::expected （异常处理） —— **半懂**
- [ ] `noexcept` noexcept （异常处理） ——**不会**
- [ ] `dynamic-cast` 动态类型转换（dynamic_cast） （语言概念（Language concepts） > 类型转换（type casting）） —**半懂**
- [ ] `reinterpret-cast` reinterpret_cast （语言概念（Language concepts） > 类型转换（type casting）） —半懂
- [ ] `undefined-behavior` 未定义行为 （Undefined Behavior，UB) （语言概念（Language concepts）） —— **不会**
- [ ] `argument-dependent-lookup` 参数依赖查找（Argument-dependent lookup，ADL) （语言概念（Language concepts）） —— **不会**
- [ ] `constexpr-consteval` constexpr / consteval （语言概念（Language concepts）） ——**&#x20;不会**
- [ ] `move-semantics` 移动语义 （语言概念（Language concepts）） ——**&#x20;不会**
- [ ] `value-categories` 值类别（lvalue/rvalue） （语言概念（Language concepts） > 移动语义） ——**不会**
- [ ] `std-move-std-forward` std::move / std::forward （语言概念（Language concepts） > 移动语义） —— **不会**
- [ ] `std-format-std-print` std::format / std::print （标准程序库+标准模板库（Standard library + STL） > 输入输出流（iostream）） ——&#x20;**&#x20;半懂&#x20;**
- [ ] `std-span-std-string` std::span / std::string_view （标准程序库+标准模板库（Standard library + STL） > 容器（Containers）） —— **半懂&#x20;**
- [ ] `multithreading` 多线程（Multithreading） （标准程序库+标准模板库（Standard library + STL）） —— **半懂&#x20;**
- [ ] `variadic-templates` 可变参数模板 (Variadic templates) （模板（Template）） —— **半懂&#x20;**
- [ ] `the-template-specialization` 模板特化（Template specialization） （模板（Template）） ——&#x20;**&#x20;不会**
- [ ] `the-full-template-specialization` 模板全特化（Full template specialization） （模板（Template） > 模板特化（Template specialization）） —— **不会**
- [ ] `the-partial-template-specialization` 模板偏特化（Partial template specialization） （模板（Template） > 模板特化（Template specialization）） ——**不会**
- [ ] `concepts` Concepts (C++20) （模板（Template）） ——**不会**
- [ ] `pimpl` pimpl（指向实现的指针） （惯常用法/设计习语（Idioms）） ——**不会**
- [ ] `non-copyable-non-moveable` Non-Copyable （不可复制）/Non-Moveable（不可移动） （惯常用法/设计习语（Idioms）） —— **不会**
- [ ] `erase-remove` Erase-Remove（删除） （惯常用法/设计习语（Idioms）） —— **不会**
- [ ] `copy-and-swap` Copy and swap（复制并交换） （惯常用法/设计习语（Idioms）） ——**不会**
- [ ] `copy-on-write` Copy on write（写时复制） （惯常用法/设计习语（Idioms）） —— **不会**
- [ ] `crtp` CRTP（奇异递归模板） （惯常用法/设计习语（Idioms）） —— **不会**
- [ ] `cpp20` C++20 （标准（Standards）） ——**半懂**

### 工具链

- [ ] `linters` Linters （使用源代码） —— **会&#x20;**
- [ ] `cmake` CMake （构建系统（Build systems）） ——**不会**
- [ ] `boost` boost （库（Library)） ——**不会**
- [ ] `gtest-gmock` gtest/gmock （框架（Frameworks）） ——**不会**

### 通用工程

- [ ] `computers-science-algorithms` 算法 （计算机科学） —— **会 / 半懂 / 不会**
- [ ] `finite-state-machines` 有限状态机（Finite-state machines） （计算机科学） —— **会 / 半懂 / 不会**
- [ ] `bduf` BDUF (Big Design Up Front) 前期大型设计 （最佳实践 > 代码质量 > 开发原则） —— **会 / 半懂 / 不会**
- [ ] `composition-is-preferably-than` Composition is preferably than the inheritance 组合优于继承 （最佳实践 > 代码质量 > 开发原则） —— **会 / 半懂 / 不会**
- [ ] `occam-s-razor` Occam's razor 奥卡姆剃刀原理（简约法则） （最佳实践 > 代码质量 > 开发原则） —— **会 / 半懂 / 不会**
- [ ] `divide-and-conquer` Divide and Conquer 分治法 （最佳实践 > 代码质量 > 开发原则） —— **会 / 半懂 / 不会**
- [ ] `skill-to-review-code` 评审代码的能力 （最佳实践 > 代码质量 > 代码评审（Code review）） —— **会 / 半懂 / 不会**
- [ ] `performance-tests` 性能测试（Performance tests） （最佳实践 > 代码质量 > 软件生命周期 > 测试） —— **会 / 半懂 / 不会**
- [ ] `software-architecture-and-components` 软件架构和组件设计 （最佳实践 > 代码质量 > 软件生命周期） —— **会 / 半懂 / 不会**
- [ ] `components-integration` 组件集成 （最佳实践 > 代码质量 > 软件生命周期） —— **会 / 半懂 / 不会**
- [ ] `deployment` 软件部署（Deployment） （最佳实践 > 代码质量 > 软件生命周期） —— **会 / 半懂 / 不会**
- [ ] `code-analyzers` 代码分析器（Code analyzers） （最佳实践 > 代码质量） —— **会 / 半懂 / 不会**
- [ ] `static-analyzers` 静态分析器（Static analyzers） （最佳实践 > 代码质量 > 代码分析器（Code analyzers）） —— **会 / 半懂 / 不会**
- [ ] `dynamic-analyzers` 动态分析器（Dynamic analyzers） （最佳实践 > 代码质量 > 代码分析器（Code analyzers）） —— **会 / 半懂 / 不会**
- [ ] `profilers` Profilers （最佳实践 > 代码质量 > 代码分析器（Code analyzers） > 动态分析器（Dynamic analyzers）） —— **会 / 半懂 / 不会**
- [ ] `licensing-risks-of-generated` 生成代码的许可风险 （最佳实践 > AI 工具） —— **会 / 半懂 / 不会**
- [ ] `usage-of-other-programming` 其他编程语言的使用 （最佳实践） —— **会 / 半懂 / 不会**
- [ ] `language-interoperability` 语言互操作性（Language interoperability） （最佳实践） —— **会 / 半懂 / 不会**
- [ ] `design-patters` 设计模式 Design Patters (GoF) （软件设计） —— **会 / 半懂 / 不会**
- [ ] `structural` 结构模式（Structural） （软件设计 > 设计模式 Design Patters (GoF)） —— **会 / 半懂 / 不会**
- [ ] `behavioral` 行为模式（Behavioral） （软件设计 > 设计模式 Design Patters (GoF)） —— **会 / 半懂 / 不会**
- [ ] `creational` 创建模式（Creational） （软件设计 > 设计模式 Design Patters (GoF)） —— **会 / 半懂 / 不会**
- [ ] `solid` SOLID （软件设计 > 面向对象编程 (OOP)） —— **会 / 半懂 / 不会**
- [ ] `uml` UML （软件设计） —— **会 / 半懂 / 不会**
- [ ] `behavior-driven-development` 行为驱动开发（Behavior Driven Development） （软件设计 > 开发方法论） —— **会 / 半懂 / 不会**

### 操作系统与并发

- [ ] `global-memory` 全局内存（Global memory） （内存 > 内存抽象（Memory abstractions）） —— **会 / 半懂 / 不会**
- [ ] `application-memory` 应用内存（Application memory） （内存 > 内存抽象（Memory abstractions）） —— **会 / 半懂 / 不会**
- [ ] `memory-alignment` 内存对齐（Memory alignment） （内存） —— **会 / 半懂 / 不会**
- [ ] `concurrency` 并发（Concurrency） （线程（Threads） > 多线程） —— **会 / 半懂 / 不会**
- [ ] `mutexes` 互斥锁 （Mutexes） （线程（Threads） > 多线程 > 并发（Concurrency）） —— **会 / 半懂 / 不会**
- [ ] `semaphores` 信号量（Semaphores） （线程（Threads） > 多线程 > 并发（Concurrency）） —— **会 / 半懂 / 不会**
- [ ] `lock-free` 无锁（lock-free） （线程（Threads） > 多线程 > 并发（Concurrency）） —— **会 / 半懂 / 不会**
- [ ] `condition-variable` condition_variable （线程（Threads） > 多线程） —— **会 / 半懂 / 不会**
- [ ] `future-promise-async` future / promise / async （线程（Threads） > 多线程） —— **会 / 半懂 / 不会**
- [ ] `event-handling` 事件处理（Event handling） （线程（Threads） > 多线程） —— **会 / 半懂 / 不会**
- [ ] `sync` 同步（Sync） （线程（Threads） > 多线程 > 事件处理（Event handling）） —— **会 / 半懂 / 不会**
- [ ] `async` 异步（Async） （线程（Threads） > 多线程 > 事件处理（Event handling）） —— **会 / 半懂 / 不会**
- [ ] `interprocess-communication` 进程间通信（Interprocess communication） （过程（Process）） —— **会 / 半懂 / 不会**
- [ ] `shared-memory` 共享内存（Shared memory） （过程（Process） > 进程间通信（Interprocess communication）） —— **会 / 半懂 / 不会**
- [ ] `pipes` 管道（Pipes） （过程（Process） > 进程间通信（Interprocess communication）） —— **会 / 半懂 / 不会**
- [ ] `serialization` 序列化（Serialization） （过程（Process） > 进程间通信（Interprocess communication）） —— **会 / 半懂 / 不会**
- [ ] `json` json （过程（Process） > 进程间通信（Interprocess communication） > 序列化（Serialization）） —— **会 / 半懂 / 不会**
- [ ] `http` HTTP （网络（Network） > TCP/IP） —— **会 / 半懂 / 不会**
- [ ] `file-system` 文件系统（File system）  —— **会 / 半懂 / 不会**
- [ ] `vulnerabilities-buffer-overflow-use` 漏洞：buffer overflow、use-after-free （程序安全） —— **会 / 半懂 / 不会**
- [ ] `sanitizers` Sanitizers (ASan / TSan / UBSan) （程序安全） —— **会 / 半懂 / 不会**

### 软技能·学习思考

- [ ] `experimenting` 实验实操  —— **会 / 半懂 / 不会**

### 软技能·思考

- [ ] `systems` 系统性  —— **会 / 半懂 / 不会**
- [ ] `critical` 批判性  —— **会 / 半懂 / 不会**
- [ ] `creative` 创意性  —— **会 / 半懂 / 不会**

### 软技能·责任

- [ ] `initiative` 主动性  —— **会 / 半懂 / 不会**
- [ ] `independence` 独立  —— **会 / 半懂 / 不会**
- [ ] `problem-solving` 解决问题  —— **会 / 半懂 / 不会**

### 软技能·资源管理

- [ ] `taking-decisions` 作决定  —— **会 / 半懂 / 不会**
- [ ] `blind-typing` 盲打  —— **会 / 半懂 / 不会**

### 软技能·沟通

- [ ] `persuasion` 说服 （协商） —— **会 / 半懂 / 不会**
- [ ] `ability-to-communicate-ideas` 团队内部交流创意和想法的能力 （协商） —— **会 / 半懂 / 不会**
- [ ] `presentation` 演讲演示  —— **会 / 半懂 / 不会**
- [ ] `written-communication-skill` 书面沟通技巧  —— **会 / 半懂 / 不会**

### 软技能·团队

- [ ] `support-team-members` 支持帮助团队成员  —— **会 / 半懂 / 不会**
- [ ] `work-in-a-distributed` 在分布式团队中工作  —— **会 / 半懂 / 不会**
- [ ] `providing-feedback` 提供意见反馈  —— **会 / 半懂 / 不会**

### 软技能·情商

- [ ] `empathy` 共情  —— **会 / 半懂 / 不会**

### 软技能·业务视野

- [ ] `understanding-the-development-context` 理解开发背景  —— **会 / 半懂 / 不会**

## 高级 Senior（重点补齐）

### 语法

- [ ] `macros` 宏（Macros） （语言概念（Language concepts）） —— **会 / 半懂 / 不会**
- [ ] `perfect-forwarding` 完美转发（Perfect forwarding） （语言概念（Language concepts） > 移动语义） —— **会 / 半懂 / 不会**
- [ ] `coroutines` Coroutines (C++20) （语言概念（Language concepts）） —— **会 / 半懂 / 不会**
- [ ] `std-ranges` std::ranges （标准程序库+标准模板库（Standard library + STL） > 算法（Algorithms）） —— **会 / 半懂 / 不会**
- [ ] `type-traits` 类型特征（type traits） （模板（Template）） —— **会 / 半懂 / 不会**
- [ ] `sfinae` SFINAE （模板（Template）） —— **会 / 半懂 / 不会**
- [ ] `cpp23` C++23 （标准（Standards）） —— **会 / 半懂 / 不会**

### 工具链

- [ ] `working-stages-of-compilers` 编译器的编译过程 （编译器（Compilers） > 对编译过程的基本了解） —— **会 / 半懂 / 不会**

### 通用工程

- [ ] `collecting-requirements` 征集要求 （最佳实践 > 代码质量 > 软件生命周期） —— **会 / 半懂 / 不会**
- [ ] `end-of-a-software` 软件生命周期结束 （最佳实践 > 代码质量 > 软件生命周期） —— **会 / 半懂 / 不会**
- [ ] `architecture-styles` 软件架构风格 （软件设计） —— **会 / 半懂 / 不会**
- [ ] `component-based` 基于组件 Component-based （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `monolithic-application` 单体式应用程序 Monolithic application （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `layered` 分层模式 Layered （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `client-server` 客户/服务器模式 Client-server （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `microservices-architecture` 微服务架构 Microservices architecture （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `event-driven` 事件驱动架构 Event-driven （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `plug-ins` 插件Plug-ins （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `rest` REST （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**
- [ ] `service-oriented-architecture` 面向服务的架构 Service-oriented architecture （软件设计 > 软件架构风格） —— **会 / 半懂 / 不会**


- [ ] `architecture-patterns` 架构模式 （软件设计） —— **会 / 半懂 / 不会**
- [ ] `mvc` MVC 模型-视图-控制器模式 （软件设计 > 架构模式） —— **会 / 半懂 / 不会**
- [ ] `mvvm` MVVM （软件设计 > 架构模式） —— **会 / 半懂 / 不会**
- [ ] `three-tier` Three-tier 三层架构 （软件设计 > 架构模式） —— **会 / 半懂 / 不会**
- [ ] `onion` Onion （软件设计 > 架构模式） —— **会 / 半懂 / 不会**
- [ ] `hexagon` Hexagon （软件设计 > 架构模式） —— **会 / 半懂 / 不会**
- [ ] `domain-driven-design` 领域驱动设计（Domain Driven Design） （软件设计 > 开发方法论） —— **会 / 半懂 / 不会**

### 操作系统与并发

- [ ] `memory-management` 内存管理（Memory management） （内存） —— **会 / 半懂 / 不会**
- [ ] `virtual-memory` 虚拟内存（Virtual memory） （内存） —— **会 / 半懂 / 不会**
- [ ] `std-atomic-cpp-memory` std::atomic，C++ 内存模型 （线程（Threads） > 多线程） —— **会 / 半懂 / 不会**
- [ ] `task-scheduler` 任务调度（Task scheduler）  —— **会 / 半懂 / 不会**

### 软技能·学习思考

- [ ] `manage-knowledge` 知识管理  —— **会 / 半懂 / 不会**

### 软技能·思考

- [ ] `strategic` 策略  —— **会 / 半懂 / 不会**

### 软技能·资源管理

- [ ] `multitasking` 多重任务同时进行  —— **会 / 半懂 / 不会**

### 软技能·沟通

- [ ] `providing-information-to-people` 向团队以外的人员提供信息的能力 （协商 > 团队内部交流创意和想法的能力） —— **会 / 半懂 / 不会**
- [ ] `finding-compromises` 寻求妥协 （协商） —— **会 / 半懂 / 不会**
- [ ] `dispute-resolution` 解决争议 （协商） —— **会 / 半懂 / 不会**
- [ ] `networking` 社交  —— **会 / 半懂 / 不会**

### 软技能·团队

- [ ] `leadership` 领导力  —— **会 / 半懂 / 不会**
- [ ] `assigning-and-clarifying-tasks` 向员工分配和明确任务 （领导力） —— **会 / 半懂 / 不会**
- [ ] `planning-and-goal-setting` 计划并制订目标 （领导力） —— **会 / 半懂 / 不会**
- [ ] `mentoring` 启导、指导他人  —— **会 / 半懂 / 不会**
- [ ] `delegation` 委派工作  —— **会 / 半懂 / 不会**

### 软技能·业务视野

- [ ] `customer-focus` 以客户为中心  —— **会 / 半懂 / 不会**
- [ ] `technology` 技术  —— **会 / 半懂 / 不会**
- [ ] `trends` 发展趋势  —— **会 / 半懂 / 不会**
