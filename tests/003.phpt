--TEST--
configuration_test2() Basic test
--SKIPIF--
<?php
if (!extension_loaded('configuration')) {
	echo 'skip';
}
?>
--FILE--
<?php
var_dump(configuration_test2());
var_dump(configuration_test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
