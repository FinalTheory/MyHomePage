<?php
$text = $_POST['text'];
$name = $_POST['name'];
if (!empty($text)) {
	$temp = tempnam("/tmp","PHP_TEMP_");
	$fid = fopen($temp, "w");
	fwrite($fid, $text);
	fclose($fid);
	$cmd = "/usr/local/bin/RunAsUser /usr/bin/mutt -s \'New Blog Comment by ".$name."\' -e \' set content_type=\'text/html\' \' -e \' set realname=\'".$name."\' \' 852301601@qq.com < ".$temp;
	system($cmd, $status);
	unlink($temp);
	if ( $status == 0 ) echo "您的留言已经成功发送";
	else echo "系统错误，您的留言发送失败，请手动发送邮件。";
} else {
	echo "Please use POST method.";
}
?>
