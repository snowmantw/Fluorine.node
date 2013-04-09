
BUILD=build
NODE_GYP=node-gyp
CONFIG=configure
MODULES=toy
ROOT=$(shell pwd)
SOURCE=source
NODEROOT="."

clean:
	rm -rf $(BUILD)/*

$(MODULES): 
	cd $(CONFIG)/$@ &&\
	test $(NODEROOT) == "." && $(NODE_GYP) configure || $(NODE_GYP) --nodedir $(NODEROOT) configure &&\
	cd build &&\
	make &&\
	test ! -e $(ROOT)/$(BUILD)/$@ && mkdir $(ROOT)/$(BUILD)/$@ || : &&\
	mv Release/$@.node $(ROOT)/$(BUILD)/$@/ &&\
	cp $(ROOT)/$(SOURCE)/$@/test.js $(ROOT)/$(BUILD)/$@/

.PHONY: clean  
