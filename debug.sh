# run server in galileo
ssh gus@galileo51
gdbserver host:port blink # host = macbook ip

# run locally
kdbg -r galileo51:port blink