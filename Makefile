SUBDIRS=examples plugin editor script tests sources

.PHONY: subdirs $(SUBDIRS)
     
subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	@echo [Subdir] $@
	@$(MAKE) -C $@

clean:
	@echo [Cleaning]
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

examples: editor sources

plugin: editor

sources: script

editor: script

tests: script
