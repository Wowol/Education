#/bin/bash

python3 server.py > server_test_output &
server_pid=$!
sleep 1
python3 test_client.py > client_test_output
sleep 3

kill $server_pid 2> /dev/null
if [ "$?" -ne "0" ] ; then
    diff server_test_output client_test_output
    exit $?
else
    echo "ERROR!"
    exit 1
fi