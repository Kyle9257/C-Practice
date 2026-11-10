# -*- coding: utf-8 -*-
import re

dsl = open('structure.dsl', encoding='utf-8').read()
tsv = open('zh.tsv', encoding='utf-8').read()

name = {}
for line in tsv.splitlines():
    if '\t' in line:
        k, v = line.split('\t', 1)
        name[k.strip()] = v.strip()

nodes = []
for raw in dsl.splitlines():
    line = raw.rstrip()
    if not line or line.lstrip().startswith(('#', 'hint ', 'spine ')):
        continue
    m = re.match(r'^(\s*)\[([A-Za-z0-9_-]+)\](.*)$', line)
    if not m:
        continue
    level = len(m.group(1)) // 2
    nid = m.group(2)
    rest = m.group(3)
    grade = 'junior'
    g = re.search(r'grade=(\w+)', rest)
    if g:
        grade = g.group(1)
    nodes.append((level, nid, grade))

# 一级分组顺序（level 1 的节点）
order = {
    'language-syntax': '语法', 'language-tools': '工具链', 'common-skills': '通用工程',
    'software-design': '软件设计', 'operating-systems': '操作系统与并发',
    'ability-to-learn': '软技能·学习思考', 'manage-mistakes': '软技能·错误管理',
    'thinking': '软技能·思考', 'responsibility': '软技能·责任',
    'manage-resources': '软技能·资源管理', 'communication': '软技能·沟通',
    'team-work': '软技能·团队', 'emotional-intelligence': '软技能·情商',
    'understanding-the-development-context': '软技能·业务视野',
}

GRADE_LABEL = {'middle': '中', 'senior': '高'}

groups = {}  # group_key -> list of (path_cn, cn, id, grade)
stack = []
for level, nid, grade in nodes:
    while stack and stack[-1][0] >= level:
        stack.pop()
    stack.append((level, nid))
    if grade not in ('middle', 'senior'):
        continue
    # level1 分组
    gkey = stack[1][1] if len(stack) >= 2 else stack[0][1]
    path_cn = ' > '.join(name.get(s[1], s[1]) for s in stack[2:-1]) if len(stack) >= 3 else ''
    cn = name.get(nid, nid)
    groups.setdefault(gkey, []).append((path_cn, cn, nid, grade))

out = []
out.append('# C++ 学习路线 · 三档标注清单（Middle + Senior）')
out.append('')
out.append('> 标注方法：每行把「会 / 半懂 / 不会」改成你的结论；已彻底掌握的整行删掉即可。')
out.append('> 标完「半懂/不会」的节点，就是下一步要补的缺口。')
out.append('')

for title, target_grade in (('中级 Middle（应已达标，用于自检）', 'middle'), ('高级 Senior（重点补齐）', 'senior')):
    out.append('## ' + title)
    out.append('')
    for k in order:
        items = [g for g in groups.get(k, []) if g[3] == target_grade]
        if not items:
            continue
        out.append('### ' + order.get(k, k))
        for path_cn, cn, nid, grade in items:
            prefix = ('（' + path_cn + '）') if path_cn else ''
            out.append('- [ ] `%s` %s %s —— **会 / 半懂 / 不会**' % (nid, cn, prefix))
        out.append('')

with open('../C++路线图标注清单.md', 'w', encoding='utf-8') as f:
    f.write('\n'.join(out))

# 统计
import collections
c = collections.Counter()
for k, v in groups.items():
    for _, _, _, g in v:
        c[g] += 1
print('middle:', c['middle'], ' senior:', c['senior'], ' total:', c['middle'] + c['senior'])
print('groups:', len(groups))
