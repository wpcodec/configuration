--TEST--
Check if configuration is loaded
--SKIPIF--
<?php
if (!extension_loaded('configuration')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "configuration" is available';
?>
--EXPECT--
The extension "configuration" is available
