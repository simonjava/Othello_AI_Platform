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

<title>AI对战平台-注册</title>
<link rel="shortcut icon" href="black.jpg" />
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
			validatorGroup : "2",
			formID : "register",
			onSuccess : function() {
				return true;
			},
			onError : function(msg) {
				alert(msg);
				return false;
			}
		});
		$("#id_new").formValidator({
			validatorGroup : "2",
			onShow : "请输入用户名",
			onFocus : "用户名至少3位，至多10个位，必须为英文字符",
			onCorrect : "用户名格式正确"
		}).inputValidator({
			min : 3,
			max : 10,
			onError : "用户名不合法,请确认!"
		}).regexValidator({
			regExp : "[^\u4E00-\u9FA0]+$",
			onError : "user_name must be English"
		});
		$("#password_new").formValidator({
			validatorGroup : "2",
			onShow : "请输入密码",
			onFocus : "密码不能为空",
			onCorrect : "密码格式正确"
		}).inputValidator({
			min : 1,
			empty : {
				leftEmpty : false,
				rightEmpty : false,
				emptyError : "密码两边不能有空格"
			},
			onError : "确保你的密码不为空"
		});
		$("#password_new_again").formValidator({
			validatorGroup : "2",
			onShow : "再次输入你的密码",
			onFocus : "密码不能为空",
			onCorrect : "密码一致"
		}).inputValidator({
			min : 1,
			empty : {
				leftEmpty : false,
				rightEmpty : false,
				emptyError : "密码两边不能有空格"
			},
			onError : "确保你的密码不为空"
		}).compareValidator({
			desID : "password_new",
			operateor : "=",
			onError : "两次密码不一致"
		});

	});
</script>
</head>
<body>
	<div id="wrapper">
		<!-- #wrapper -->
		<a href="login.jsp"> <header> <!-- header --> </header> </a>
		<!-- end of header -->
		<section id="main"> <!-- #main content and sidebar area -->
		<section id="content"> <!-- #content --> <article>
		<h2>注册</h2>
		<form name="register" id="register" action="RegisterServlet"
			method="post">
			<div class="wrap">
				<div class="label">
					<p>用户名：</p>
				</div>
				<div>
					<input id="id_new" type="text" name="id_new" class="text_field" />
				</div>
				<div id="id_newTip"></div>
			</div>
			<div style="clear: both;"></div>
			<div class="wrap">
				<div class="label">
					<p>密码：</p>
				</div>
				<div>
					<input id="password_new" type="password" name="password_new"
						class="text_field" />
				</div>
				<div id="password_newTip"></div>
			</div>
			<div style="clear: both;">
				<div class="wrap">
					<div class="label">
						<p>确认：</p>
					</div>
					<div>
						<input id="password_new_again" type="password"
							name="password_new_again" class="text_field" />
					</div>
					<div id="password_new_againTip"></div>
				</div>
				<div style="clear: both;"></div>
				<div>
					<input id="submit2" type=submit value="注册" /> <input type=reset
						value="重置" />
				</div>
		</form>
		</article>
		<hr />
		<%@include file="Desc.txt"%> </section> <!-- end of #content -->

		<aside id="sidebar"> <!-- sidebar --> <h3>
				Things To Do
			</h3>
			<ul>
				<li>
					<a href="example.txt" target="_blank">示例程序</a>
				</li>
				<li>
					<a href="rank.jsp">所有排名</a>
				</li>
				<li>
					<a href="update.txt" target="_blank">更新说明</a>
				</li>
				<li>
					<a href="forum.jsp" target="_blank">讨论论坛</a>
				</li>
			</ul>


			<h3>
				Connect With Us
			</h3>
			<ul>
				<li>
					chengsm@mail.ustc.edu.cn
				</li>
				<li>
					danewang@mail.ustc.edu.cn
				</li>
			</ul>
			
			<h3>
				待定
			</h3>
		</aside> <!-- end of sidebar --> </section>
		<!-- end of #main content and sidebar-->

		<%@include file="Foot"%>

	</div>
	<!-- #wrapper -->
	<!-- Free template created by http://bestmoban.com -->
</body>
</html>
<%@ include file="fuckIE"%>
