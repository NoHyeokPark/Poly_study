<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<style>
#content > * {
width: 80%;
}


</style>
<script type="text/javascript">
let checkForm = function(){
	let f = document.wFrom
	if(f.title.value == ''){
		f.title.focus()
		return false
	}
	if(f.writer.value == ''){
		f.writer.focus()
		return false
	}
	if(f.content.value == ''){
		f.content.focus()
		return false
	}
	return true
}
</script>
</head>
<body>
<div align="center" id='content'>
<hr><h2>새 글 등록</h2><hr>
<form name='wFrom' action="write.jsp" method='post' onsubmit="return checkForm()">
<table border='1' style='width:80%;'>
<tr>
<th>제목</th>
<td><input type='text' name='title' size='120'></td>
</tr>

<tr>
<th>작성자</th>
<td><input type='text' name='writer' size='10' required="required"></td>
</tr>

<tr>
<th>내용</th>
<td><textarea name='content' rows='20' cols='150' required="required"></textarea></td>
</tr>
</table>
<br>
<button type='submit'>등록</button>
</form>
</div>
</body>
</html>