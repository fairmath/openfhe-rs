#!/usr/bin/env bash

original_version_str="$(cat ${GITHUB_WORKSPACE}/Cargo.toml | grep "version = ")"
version_number="$(echo ${original_version_str} | cut -d "\"" -f2)"

major="${version_number%%.*}"
version_number="${version_number#*.}"
minor="${version_number%%.*}"
patch="${version_number#*.}"

if [[ ${CHANGE_TYPE} == "major" ]]
then
  major=$((major+1))
elif [[ ${CHANGE_TYPE} == "minor" ]]
then
  minor=$((minor+1))
else
  patch=$((patch+1))          
fi

new_version_str='version = "'${major}.${minor}.${patch}'"'
sed -i "s|${original_version_str}|${new_version_str}|g" ${GITHUB_WORKSPACE}/Cargo.toml

