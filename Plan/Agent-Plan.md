
https://tech.meituan.com/2026/08/07/Agent-Evaluation.html
https://www.zhihu.com/question/1890240528236393875














# Harness
通过上下文管理和工具接口定义，提供约束；验证；纠错的功能
## action 追踪
## 约束 审查 hooks
## 验证 evidence based
## 纠错

# Tool
## Function calling & MCP

# Memory
## Memory 类型
## Memory范式
- Input  
添加 add  何时添加  
编码 Encoding  

- Inside  
自动整理 summary consolidate  
      
遗忘 fogrtting  
- Output  
检索 retrieval 何时召回


# Evaluaion
对比试验 消融实验
换模型 deepseek flash 和 qwen 3.7
Pass^k 连续运行k次得到正确结果

渐进式披露，模拟真实用户
# Design
渐进式披露
Borrow R/W | Move + R/W（Inside决定）
- Input  

- Inside  

- Output

---

## 公用
### 适用场合
- 通用型
> 一般workflow 对用户的习惯记录要求高，配置，默认配置，临时更改默认，重写默认，（无视默认）提示

> 对环境的感知：你的眼，要看向哪些东西
- 专业型
### 内容
- 原始内容 raw rollout data  

- 不安全内容不要存储
- 存储 与 索引  
mcp与function calling的对比，tool_list的获取
### 行为
- 不要欺骗，
- 最小修改 （对已有代码？编写的思路能这么按照吗）
- 危险操作前的提醒
### 评测
- NO-OP “未来的 agent 是否有理由会因为我在这里写下的内容而表现得更好？”
- 采集：采集线上或沙箱中的原始任务数据
- 清洗：去重、归类、补上下文、修复脏数据
- 评测：人工评测、AI 评测
- 质检：检查评测标准是否稳定、评测结果是否可信
- 分析/归因：定位问题归因，形成优化建议和回归任务
### 交付（最后的检查）










