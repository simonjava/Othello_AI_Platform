<%@page import="com.csm.fileUtil.StreamUtil"%>
<%@page import="com.platform.entity.Task"%>
<%@page import="com.platform.operator.TaskOperator"%>
<%@page import="java.nio.charset.Charset"%>
<%@page import="java.nio.ByteBuffer"%>
<%@page language="java" import="java.util.*" pageEncoding="UTF-8"%>


<%
	String id = (String) session.getAttribute("id");
	String user_id = id;
	String game = request.getParameter("game");
	Task task = TaskOperator.getTaskByIdAndGame(user_id, game);
	String code = Charset.forName("utf-8")
			.decode(ByteBuffer.wrap(task.getCode())).toString();
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<title>代码查看</title>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />

</head>
<body>
	<pre>
		<%code = code.replaceAll("<", "&lt;").replaceAll(">", "&gt;"); %>
		<%=code %>
	</pre>
</body>
</html>