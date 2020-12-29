# syntax tree
# t - token
# s - syntax rule

rule [t:type(t) t:doubleDot t:name t:openBrace t:matchValue t:closeBrace]
rule [t:type(s) t:doubleDot t:name]
rule [t:type(t) t:doubleDot t:name]
ruleList [s:rule s:rule]
ruleList [s:ruleList s:rule]
ruleList [s:ruleList s:ruleList]
record [t:name t:open s:rule t:close]
record [t:name t:open s:ruleList t:close]
tree [s:record s:record]
tree [s:record]
tree [s:tree s:tree]
