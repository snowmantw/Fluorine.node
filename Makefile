
BUILD = build
NODE_WAF = node-waf

toy: 
	node-waf configure build

.PHONY: toy 
