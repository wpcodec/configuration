--TEST--
configuration_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('configuration')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = configuration_test1();

var_dump($ret);
?>
--EXPECT--
The extension configuration is loaded and working!
NULL
