# syntax tree
# t - token
# s - syntax rule

s:rule [t:rule]
s:rule [t:token]
s:ruleList [s:rule s:rule]
s:ruleList [s:ruleList s:rule]
s:record [t:name t:open s:rule t:close]
s:record [t:name t:open s:ruleList t:close]
