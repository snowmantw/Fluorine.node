
BUILD=build
NODE_GYP=node-gyp
CONFIG=configure
MODULES=toy
ROOT=$(shell pwd)

clean:
	rm -rf $(BUILD)/*

$(MODULES): 
	cd $(CONFIG)/$@ &&\
	$(NODE_GYP) configure &&\
	cd build &&\
	make &&\
	test ! -e $(ROOT)/$(BUILD)/$@ && mkdir $(ROOT)/$(BUILD)/$@ || : &&\
	mv Release/$@.node $(ROOT)/$(BUILD)/$@/

.PHONY: clean  
