<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />

<title>AI对战平台-提交代码</title>
<link rel="stylesheet" type="text/css" href="css/styles.css"
	media="screen" />
<link rel="stylesheet" type="text/css" href="css/print.css"
	media="print" />
<!--[if IE]><script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
<!-- jQuery -->
<script type="text/javascript" src="js/jquery-1.4.4.min.js"></script>
<!-- 数据验证 -->
<script src="formValidator/jquery-1.4.4.min.js" type="text/javascript"></script>
<script src="formValidator/formValidator-4.1.3.js"
	type="text/javascript" charset="UTF-8"></script>
<script src="formValidator/formValidatorRegex.js" type="text/javascript"
	charset="UTF-8"></script>

<!-- 具体验证 -->
<script type="text/javascript">
	$(document).ready(function() {

		$.formValidator.initConfig({
			formID : "submitCode",
			onSuccess : function() {
				return true;
			},
			onError : function(msg) {
				alert(msg);
				return false;
			}
		});
		$("#code").formValidator({}).inputValidator({
			min : 10,
			onError : "How could such a short code"
		});

	});
</script>
</head>
<body>
	<div id="wrapper">
		<!-- #wrapper -->
		<a href="main.jsp"> <header> <!-- header --> </header> </a>
		<!-- end of header -->



		<!-- start of top nav -->
		<%@include file="Nav.txt"%>
		<!-- end of top nav -->
		<section id="content"> <!-- #content --> <article>
		<h2>submit your code</h2>

		<form name="submitCode" id="submitCode" action="SubmitCodeServlet"
			method="post" onsubmit="return All();">
			<div>
				Compile Environment: <select name="compile_environment"
					id="compile_environment"
					style="width: 100px; height: 30px; font-size: 20px;">
					<option value="gcc" selected="selected">gcc</option>
					<option value="g++" >g++</option>
				</select> Game: <select name="game" id="game"
					style="width: 100px; height: 30px; font-size: 20px;">
					<option value="othello" selected="selected">othello</option>
				</select> <input type=submit value="Submit"
					style="width: 100px; height: 30px; font-size: 20px;" />示例代码 <a
					href="example.txt" target="_blank">c</a>
					<a
					href="example2.txt" target="_blank">c++</a>
			</div>
			<textarea name="code" id="code" style="width: 800px; height: 400px;">paste your code here</textarea>
		</form>
		</article>
		<div style="margin-top: 10px; margin-bottom: 10px;">`</div>



		</section>
		<!-- end of #content -->



		<!-- end of #main content and sidebar-->

		<%@include file="Foot"%>


	</div>
	<!-- #wrapper -->
	<!-- Free template created by http://bestmoban.com -->
</body>
</html>
<%@ include file="fuckIE"%>