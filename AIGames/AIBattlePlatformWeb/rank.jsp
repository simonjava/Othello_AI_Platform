<%@page import="com.platform.common.Constant"%>
<%@page import="com.csm.common.DataUtil"%>
<%@page import="com.csm.web.pageUtil.PageModel"%>
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<%@taglib uri="http://javacrazyer.iteye.com/tags/pager" prefix="w"%>
<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<%@page import="com.platform.operator.InformationOperator"%>
<%@page import="com.platform.entity.Information"%>
<%@page import="com.platform.entity.Task"%>
<%@page import="com.platform.operator.TaskOperator"%>
<%@page import="com.platform.operator.ReplayOperator"%>
<%@page import="com.platform.entity.Replay"%>
<%@page import="com.csm.web.pageUtil.PageModel"%>

<%
	PageModel<Information> pm = (PageModel<Information>) request
			.getAttribute("pm");
	if (pm == null)
	{
		response.sendRedirect("GetRankServlet");
	}
	String id = (String) session.getAttribute("id");
	boolean isLogin = false;
	if (id != null && !id.equals(""))
		isLogin = true;
	request.setAttribute("isLogin", isLogin);

	int pageNo = 1;
	pageNo = (Integer) request.getAttribute("pageNo");

	int pageSize = Constant.RANK_PAGESIZE;
	pageSize = (Integer) request.getAttribute("pageSize");
%>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<title>AI对战平台-排名</title>
<link rel="stylesheet" type="text/css" href="css/styles.css"
	media="screen" />
<link rel="stylesheet" type="text/css" href="css/print.css"
	media="print" />
<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
</head>

<body>
	<div id="wrapper">

		<!-- #wrapper -->

		<%
			if (isLogin)
			{
		%>
		<a href="main.jsp"> <%
 	} else
 	{
 %> <a href="login.jsp"> <%
 	}
 %> <header> <!-- header --> </header> </a> <!-- end of header --> <!-- start of top nav -->
			<%@include file="Nav.txt"%> <!-- end of top nav -->

			<section id="main2"> <article style="text-algin:center;">

			<table class="dataTable" style="margin: auto;width:850px">
				<caption style="font-size: 30px;text-align: left;color: #000000">所有排名</caption>
				<thead>
					<tr>
						<th>排名</th>
						<th>用户</th>
						<th>游戏</th>
						<th>比赛次数</th>
						<th>胜利次数</th>
						<th>得分</th>
						<%
							if (isLogin)
							{
						%>
						<th>操作</th>
						<%
							}
						%>
					</tr>
				</thead>
				<tbody>

					<%
						int r = 0;
						for (Information in : pm.getDatas())
						{
							r++;
					%>
					<tr <%if (r % 2 == 0)
				{%> class="odd" <%}%>>
						<td><%=(r + (pageNo - 1) * pageSize)%></td>
						<%
							if (isLogin && id.equals(in.getUser_id()))
								{
						%>
						<td style="background: #ff0000"><%=in.getUser_id()%></td>
						<%
							} else
								{
						%>
						<td><%=in.getUser_id()%></td>
						<%
							}
						%>
						<td><%=in.getGame()%></td>
						<td><%=in.getContest_times()%></td>
						<td><%=in.getWin()%></td>
						<td><%=in.getScore()%></td>

						<%
							if (isLogin && !id.equals(in.getUser_id()))
								{
						%>
						<td><a
							href="AddReplayServlet?player2=<%=in.getUser_id()%>&game=<%=in.getGame()%>">挑战</a>
						</td>
						<%
							}
						%>
					</tr>
					<%
						}
					%>
				</tbody>
			</table>
			<w:pager pageSize="${pageSize}" pageNo="${pageNo}"
				url="GetRankServlet" recordCount="${pm.recordCount }" /> </article> </section> <!-- end of #main content and sidebar-->
			<%@ include file="Foot"%>
	</div>
	<!-- #wrapper -->
	<!-- Free template created by http://bestmoban.com -->
</body>
</html>
<%@ include file="fuckIE"%>