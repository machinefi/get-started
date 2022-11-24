BUILD_DIR=../wasm

$(BUILD_DIR)/click2earn.wasm: click2earn.go
	tinygo build -o $@ -scheduler=none -target=wasi --no-debug click2earn.go

clean:
	rm -f $(BUILD_DIR)/*